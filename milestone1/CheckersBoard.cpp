#include <assert.h>
#include <memory.h>
#include <stack>
#include "Board.h"
#include "Class.h"
#include "CheckersBoard.h"
#include "CheckersDlg.h"
#include "CheckersMove.h"
#include "CheckersView.h"
#include "BasicKey.h"

namespace {
   // Right shift the mask. Reset the mask and advance ptr, if necessary.
   inline void RightShiftMask(ulong *mask, ulong **ptr)
   {
      *mask >>= 1;
      if (!*mask) {
         *mask = 1 << CheckersBoard::kBitsPerLong - 1;
         (*ptr)++;
      }
   }

   const int kUpperBlackRow = 3;
   const int kLowerWhiteRow = 5;
}

// static
const int CheckersBoard::kDirs[] = { -1, 1 };

// static
BoardClass CheckersBoard::mClass = BoardClass("CheckersBoard",
 &CheckersBoard::Create, "Checkers", CheckersView::GetClassPtr(),
 CheckersDlg::GetClassPtr(), &CheckersBoard::GetOptions,
 &CheckersBoard::SetOptions);

// static
CheckersBoard::Rules CheckersBoard::mRules;

void CheckersBoard::Rules::EndSwap()
{
   kingWgt = EndianXfer(kingWgt);
   backRowWgt = EndianXfer(backRowWgt);
   moveWgt = EndianXfer(moveWgt);
}

CheckersBoard::CheckersBoard()
{
   Init();
}

void CheckersBoard::Init()
{
   int cellNum = 0;
   mWhoseMove = kBlack;

   // Initialize mCells.
   for (int row = 0; row < kDim; row++)
      for (int col = 0; col < kDim; col++, cellNum++)
         mCells[row][col] = new Cell(row, col, (uint64_t) 1 << cellNum);

   // Initialize pieces inside appropriate cells, modify masks accordingly.
   mBlack = 0;
   for (int row = 0; row < kUpperBlackRow; row++)
      for (int col = row % 2; col < kDim; col += 2) {
         mCells[row][col]->piece = new Piece(row, col, kBlack);
         mPieces.push_back(mCells[row][col]->piece);
         mBlack |= mCells[row][col]->mask;
      }

   mWhite = 0;
   for (int row = kLowerWhiteRow; row < kDim; row++)
      for (int col = row % 2; col < kDim; col += 2) {
         mCells[row][col]->piece = new Piece(row, col, kWhite);
         mPieces.push_back(mCells[row][col]->piece);
         mWhite |= mCells[row][col]->mask;
      }
}

long CheckersBoard::GetValue() const
{
   Piece *piece;
   long val = 0;
   std::list<Board::Move *> allMoves;

   for (std::list<Piece *>::const_iterator iter = mPieces.begin();
    iter != mPieces.end(); iter++) {
      piece = *iter;
      if (piece) {
         if (piece->rank == kRegular)
            val += mRules.pieceWgt * piece->whose;
         else
            val += mRules.kingWgt * piece->whose;
         if (piece->loc.first == piece->backRow)
            val += mRules.backRowWgt * piece->whose;
      }
   }

   val += mRules.moveWgt * mWhoseMove;

   GetAllMoves(&allMoves);
   if (allMoves.empty()) {
      if (val < 0)
         val = -kWinVal;
      else if (val > 0)
         val = kWinVal;
      else
         val = 0;
   }

   for (std::list<Board::Move *>::iterator iter = allMoves.begin();
    iter != allMoves.end(); iter++) {
      delete *iter;
   }

   return val;
}

bool CheckersBoard::MovePiece(Location &src, Location &dst)
{
   Cell *srcCell = CellAt(src);
   Cell *dstCell = CellAt(dst);

   // A piece can go in a circle! In this case, do nothing.
   if (srcCell == dstCell)
      return false;

   assert(srcCell->piece);
   assert(!dstCell->piece);

   Piece *piece = srcCell->piece;

   if (piece->whose == kBlack) {
      mBlack &= ~srcCell->mask;
      mBlack |= dstCell->mask;
   } else {
      mWhite &= ~srcCell->mask;
      mWhite |= dstCell->mask;
   }

   dstCell->piece = piece;
   srcCell->piece = NULL;
   piece->loc = dstCell->loc;

   assert(!srcCell->piece);
   assert(dstCell->piece);

   if (piece->rank == kRegular && piece->loc.first == piece->kingRow) {
      piece->rank = kKing;
      return true;
   }

   return false;
}

void CheckersBoard::AddPiece(Cell *cell)
{
   assert(!cell->piece);

   Piece *piece = mRemovedPieces.back();
   if (piece->whose == kBlack)
      mBlack |= cell->mask;
   else
      mWhite |= cell->mask;

   mRemovedPieces.pop_back();
   mPieces.push_back(piece);
   cell->piece = piece;

   assert(cell->piece);
}

void CheckersBoard::RemovePiece(Cell *cell)
{
   assert(cell->piece);

   Piece *piece = cell->piece;

   if (piece->whose == kBlack)
      mBlack &= ~cell->mask;
   else
      mWhite &= ~cell->mask;

   mRemovedPieces.push_back(piece);
   mPieces.remove(piece);
   cell->piece = NULL;

   assert(!cell->piece);
}

void CheckersBoard::ApplyMove(Move *move)
{
   CheckersMove *cm = dynamic_cast<CheckersMove *>(move);
   Piece *piece = PieceAt(cm->mLocs.front().first, cm->mLocs.front().second);

   // Remove every in-between piece.
   if (cm->IsCapture()) {
      for (unsigned int i = 1; i < cm->mLocs.size(); i++)
         RemovePiece(CellInbetween(cm->mLocs[i - 1], cm->mLocs[i]));
   }

   // Move the first to the end.
   if (MovePiece(piece->loc, cm->mLocs.back()))
      cm->mToKing = true;

   mMoveHist.push_back(move);
   mWhoseMove = -mWhoseMove;
}

void CheckersBoard::UndoLastMove()
{
   CheckersMove* cm = dynamic_cast<CheckersMove *>(mMoveHist.back());
   Piece *piece = PieceAt(cm->mLocs.back().first, cm->mLocs.back().second);

   // Add every in-between piece (backwards order).
   if (cm->IsCapture()) {
      for (int i = cm->mLocs.size() - 1; i > 0; i--)
         AddPiece(CellInbetween(cm->mLocs[i], cm->mLocs[i - 1]));
   }

   // Move the end to the first. Adjust piece rank if necessary.
   MovePiece(piece->loc, cm->mLocs.front());
   if (cm->mToKing)
      piece->rank = kRegular;

   assert(mMoveHist.size() > 0);
   mMoveHist.pop_back();
   mWhoseMove = -mWhoseMove;

   delete cm;
}

// inline
CheckersBoard::Cell *CheckersBoard::CellFrom(Location &loc, int dr,
 int dc) const
{
   if (InRange<int>(0, loc.first + dr, kDim) &&
    InRange<int>(0, loc.second + dc, kDim)) {
      return mCells[loc.first + dr][loc.second + dc];
   }

   return NULL;
}

// inline
bool CheckersBoard::IsCellEmpty(const Cell *cell) const
{
   assert(cell);
   return !(cell->mask & (mBlack | mWhite));
}

// inline
CheckersBoard::Piece *CheckersBoard::PieceAt(int row, int col) const
{
   return mCells[row][col]->piece;
}

// inline
CheckersBoard::Cell *CheckersBoard::CellAt(Location &loc) const
{
   return mCells[loc.first][loc.second];
}

// inline
CheckersBoard::Cell *CheckersBoard::CellInbetween(
 Location loc1, Location loc2) const
{
   return mCells[(loc1.first + loc2.first) / 2][(loc1.second +
    loc2.second) / 2];
}

void CheckersBoard::GetAllMoves(std::list<Move *> *moves) const
{
   Cell *dst;
   Piece *piece;


   moves->clear();
   if (mBlack == 0 || mWhite == 0)
      return;

   // Find any available captures.
   for (int row = 0; row < kDim; row++)
      for (int col = 0; col < kDim; col++)
         if ((piece = PieceAt(row, col)) && piece->whose == mWhoseMove)
            AddCaptures(piece, moves);

   // If no captures are available, add regular moves.
   if (moves->empty()) {
      for (int row = 0; row < kDim; row++) {
         for (int col = 0; col < kDim; col++) {
            if ((piece = PieceAt(row, col)) && piece->whose == mWhoseMove) {
               for (int i = 0; i < 2; i++) {
                  // Skip negative row if black regular piece.
                  if (mWhoseMove == kBlack && piece->rank == kRegular)
                     i++;

                  for (int j = 0; j < 2; j++) {
                     dst = CellFrom(piece->loc, kDirs[i], kDirs[j]);
                     if (dst && IsCellEmpty(dst)) {
                        moves->push_back(new CheckersMove(piece->loc,
                         dst->loc));
                     }
                  }

                  // Skip positive row if white regular piece.
                  if (mWhoseMove == kWhite && piece->rank == kRegular)
                     break;
               }
            }
         }
      }
   }
}

void CheckersBoard::AddCaptures(Piece *piece, std::list<Move *> *moves) const
{
   assert(piece);

   bool more; // set to true if the current "move" has "more" to do
   std::stack<LocVector> locVecStack;
   LocVector curLocs, temp;
   LocVector::const_iterator locIter;
   const Cell *dstCell;

   uint64_t *ourMask = &mBlack;
   uint64_t *theirMask = &mWhite;

   if (mWhoseMove == kWhite) {
     ourMask = &mWhite;
     theirMask = &mBlack;
   }

   temp.push_back(piece->loc);
   locVecStack.push(temp);

   while (!locVecStack.empty()) {
      curLocs = locVecStack.top();
      locVecStack.pop();

      // Set masks for the current cell and previous two.
      if (curLocs.size() > 1) {
         *ourMask |= CellAt(curLocs.back())->mask;
         *theirMask &= ~CellInbetween(curLocs.back(),
          curLocs[curLocs.size() - 2])->mask;
         *ourMask &= ~CellAt(curLocs[curLocs.size() - 2])->mask;
      }

      more = false;
      // Start with upper right, then upper left
      for (int i = 1; i >= 0; i--) {
         // Skip positive row if white regular piece.
         if (mWhoseMove == kWhite && piece->rank == kRegular)
            i--;

         for (int j = 1; j >= 0; j--) {
            if ((dstCell = CellFrom(curLocs.back(), 2 * kDirs[i],
             2 * kDirs[j]))) {
               // Ensure the next cell has an opponent's piece, and the
               // cell after that is empty.
               if (CellFrom(curLocs.back(), kDirs[i], kDirs[j])->mask &
                *theirMask && IsCellEmpty(dstCell)) {
                  temp = curLocs;
                  temp.push_back(dstCell->loc);
                  locVecStack.push(temp);

                  more = true;
               }
            }
         }

         // Skip negative row if black regular piece.
         if (mWhoseMove == kBlack && piece->rank == kRegular)
            break;
      }

      // Add this move to |moves|, and then undo the damage it did to the
      // masks.
      if (!more && curLocs.size() > 1) {
         moves->push_back(new CheckersMove(curLocs));
         for (int i = curLocs.size() - 2; i >= 0; i--) {
            *ourMask |= CellAt(curLocs[i])->mask;
            *theirMask |= CellInbetween(curLocs[i], curLocs[i + 1])->mask;
            *ourMask &= ~CellAt(curLocs[i + 1])->mask;
         }
      }
      /*
      if (!more && curLocs.size() > 1) {
         moves->push_back(new CheckersMove(curLocs));

         // Add the first piece, remove the last.
         *ourMask |= CellAt(curLocs.front())->mask;
         *ourMask &= ~CellAt(curLocs.back())->mask;

         // Add every opponent's piece back.
         for (unsigned int i = 0; i < curLocs.size() - 1; i++)
            *theirMask |= CellInbetween(curLocs[i], curLocs[i + 1])->mask;
      }
      */
   }
}

Board::Move *CheckersBoard::CreateMove() const
{
   return new CheckersMove();
}

Board *CheckersBoard::Clone() const
{
   CheckersBoard *board = new CheckersBoard();
   Piece *newPiece;


   board->mWhoseMove = mWhoseMove;
   board->mBlack = mBlack;
   board->mWhite = mWhite;

   for (std::list<Piece *>::const_iterator iter = mPieces.begin();
         iter != mPieces.end(); iter++) {
      newPiece = new Piece(**iter);
      board->mCells[newPiece->loc.first][newPiece->loc.second]->piece =
       newPiece;
      board->mPieces.push_back(newPiece);
   }

   for (std::list<Piece *>::const_iterator iter = mRemovedPieces.begin();
         iter != mRemovedPieces.end(); iter++) {
      board->mRemovedPieces.push_back(new Piece(**iter));
   }

   for (std::list<Move *>::const_iterator iter = mMoveHist.begin();
         iter != mMoveHist.end(); iter++) {
      board->mMoveHist.push_back((*iter)->Clone());
   }

   return board;
}

const Board::Key *CheckersBoard::GetKey() const
{
   BasicKey<4> *key = dynamic_cast<BasicKey<4> *>(BasicKey<4>::Create());
   Piece *piece;
   int row, col;
   ulong mask = 1 << kBitsPerLong - 2;
   ulong *lp = key->vals;

   // The MSB gets a 1 if white, 0 if black.
   // The remaining bits are packed with the following code:
   // No piece: 0
   // Black piece: 100
   // White piece: 101
   // Black king: 110
   // White king: 111
   key->vals[0] = (mWhoseMove == kWhite) << kBitsPerLong - 1;

   for (row = 0; row < kDim; row++) {
      for (col = 0; col < kDim; col++) {
         piece = mCells[row][col]->piece;

         if (piece) {
            *lp |= mask;
            RightShiftMask(&mask, &lp);
            if (piece->whose == kWhite)
               *lp |= mask;
            RightShiftMask(&mask, &lp);
            if (piece->rank == kKing)
               *lp |= mask;
         }

         RightShiftMask(&mask, &lp);
      }
   }

   return key;
}

std::istream &CheckersBoard::Read(std::istream &is)
{
   Move *temp;
   int mvCount;

   Delete();
   mMoveHist.clear();
   mPieces.clear();
   mRemovedPieces.clear();
   Init();

   is.read((char *) &mRules.kingWgt, sizeof(int));
   is.read((char *) &mRules.backRowWgt, sizeof(int));
   is.read((char *) &mRules.moveWgt, sizeof(int));
   mRules.EndSwap();

   is.read((char *) &mvCount, sizeof(int));
   mvCount = EndianXfer(mvCount);

   for (int i = 0; i < mvCount; i++) {
      temp = CreateMove();
      is >> *dynamic_cast<CheckersMove *>(temp);
      ApplyMove(temp);
   }

   return is;
}

std::ostream &CheckersBoard::Write(std::ostream &os) const
{
   Rules rls = mRules;
   int mvCount = EndianXfer((int) mMoveHist.size());
   std::list<Board::Move *>::const_iterator iter;

   rls.EndSwap();
   os.write((char *) &rls.kingWgt, sizeof(int));
   os.write((char *) &rls.backRowWgt, sizeof(int));
   os.write((char *) &rls.moveWgt, sizeof(int));

   os.write((char *) &mvCount, sizeof(int));
   for (iter = mMoveHist.begin(); iter != mMoveHist.end(); iter++)
      os << **iter;

   return os;
}

const Class *CheckersBoard::GetClass() const
{
   return &mClass;
}

// static
Object *CheckersBoard::Create()
{
   return new CheckersBoard();
}

// static
void *CheckersBoard::GetOptions()
{
   return new Rules(mRules);
}

// static
void CheckersBoard::SetOptions(const void *opts)
{
   const Rules *rules = reinterpret_cast<const Rules *>(opts);
   mRules.kingWgt = rules->kingWgt;
   mRules.backRowWgt = rules->backRowWgt;
   mRules.moveWgt = rules->moveWgt;
}

void CheckersBoard::Delete()
{
   for (std::list<Move *>::iterator iter = mMoveHist.begin();
    iter != mMoveHist.end(); iter++) {
      delete *iter;
   }

   for (std::list<Piece *>::iterator iter = mPieces.begin();
    iter != mPieces.end(); iter++) {
      delete *iter;
   }

   for (std::list<Piece *>::iterator iter = mRemovedPieces.begin();
    iter != mRemovedPieces.end(); iter++) {
      delete *iter;
   }

   for (int row = 0; row < kDim; row++)
      for (int col = 0; col < kDim; col++)
         delete mCells[row][col];
}
