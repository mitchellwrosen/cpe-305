#include <assert.h>
#include <memory.h>
#include <limits.h>
#include "Class.h"
#include "CheckersBoard.h"
#include "CheckersDlg.h"
#include "CheckersMove.h"
#include "CheckersView.h"
#include "BasicKey.h"

// static
BoardClass CheckersBoard::mClass = BoardClass("CheckersBoard",
 &CheckersBoard::Create, "Checkers", CheckersView::GetClassPtr(),
 CheckersDlg::GetClassPtr(), &CheckersBoard::GetOptions,
 &CheckersBoard::SetOptions);

// static
CheckersBoard::Rules CheckersBoard::mRules;

// static
CheckersBoard::StaticInitializer CheckersBoard::staticInitializer;

// static
void CheckersBoard::StaticInit()
{
   uint64_t mask = 1;
   for (int row = 0; row < kDim; row++)
      for (int col = 0; col < kDim; col++, mask <<= 1)
         mCells[row][col] = Cell(row, col, mask);
}

CheckersBoard::Piece::Piece(Cell *cell, int whose) : mCell(cell),
 mRank(kNormal), mWhose(whose), mKingRow(mWhose == kBlack ? kDim - 1 : 0),
 mBackRow(mWhose == kBlack ? 0 : kDim - 1)
{
}

void CheckersBoard::Rules::SetKingWgt(int val)
{
   if (val < 1 || val > 1000)
      throw BaseException("Please enter a value between 0 and 1000");

   kingWgt = val;
}

void CheckersBoard::Rules::SetBackRowWgt(int val)
{
   if (val < 1 || val > 1000)
      throw BaseException("Please enter a value between 0 and 1000");

   backRowWgt = val;
}

void CheckersBoard::Rules::SetMoveWgt(int val)
{
   if (val < 1 || val > 100)
      throw BaseException("Please enter a value between 0 and 100");

   moveWgt = val;
}

void CheckersBoard::Rules::EndSwap()
{
   kingWgt = EndianXfer(kingWgt);
   backRowWgt = EndianXfer(backRowWgt);
   moveWgt = EndianXfer(moveWgt);
}

CheckersBoard::CheckersBoard() : mWhite(0), mBlack(0), mNumWhite(8),
 mNumWhiteBackRow(4), mNumWhiteKing(0), mNumBlack(8), mNumBlackBackRow(4),
 mNumBlackKing(0), mWhoseMove(kBlack)
{
   for (int row = 0; row < 3; row++)
      for (int col = row % 1; col < kDim; col += 2)
         mBlackPieces.insert(Piece(&mCells[row][col], kBlack));
   for (int row = 5; row < kDim; row++)
      for (int col = row % 1; col < kDim; col += 2)
         mWhitePieces.insert(Piece(&mCells[row][col], kWhite));
}

long CheckersBoard::GetValue() const
{
   if (mBlack == 0)
      return kWinVal;
   if (mWhite == 0)
      return -kWinVal;

   return mRules.GetKingWgt()*(mNumBlackKing - mNumWhiteKing) +
    mRules.GetBackRowWgt()*(mNumBlackBackRow - mNumWhiteBackRow) +
    mRules.GetMoveWgt()*mWhoseMove +
    mRules.GetPieceWgt()*((mNumBlack - mNumBlackKing - mNumBlackBackRow) -
     (mNumWhite - mNumWhiteKing - mNumWhiteBackRow));
}

void CheckersBoard::MovePiece(Cell *target, Piece *piece)
{
   bool promoted;
   int &numKing = mWhoseMove == kBlack ? mNumBlackKing : mNumWhiteKing;
   int &numBackRow = mWhoseMove == kBlack ? mNumBlackBackRow :
    mNumWhiteBackRow;
   int &numNormal = mWhoseMove == kBlack ? mNumBlack : mNumWhite;
   bool kingBefore = piece->GetRank() == Piece::kKing;
   bool backRowBefore = piece->IsOnBackRow();

   // You should never be able to move a piece not belonging to the current
   // player, nor should you be able to move to an occupied cell.
   assert(piece->GetWhose() == mWhoseMove);
   assert(!PieceAt(target));

   HalfMove(target, piece);

   // Normal piece to king.
   if (!kingBefore && piece->GetRank() == Piece::kKing) {
      numKing++;
      numNormal--;
   }

   // Middle piece to back row piece or vice versa.
   if (!backRowBefore && piece->IsOnBackRow()) {
      numBackRow++;
      numNormal--;
   } else if (backRowBefore && !piece->IsOnBackRow()) {
      numBackRow++;
      numNormal--;
   }
}

void CheckersBoard::ApplyMove(Move *move)
{
   /*
   CheckersMove *tm = dynamic_cast<CheckersMove *>(move);
   int rChange = -1;  // Start by assuming we'll lose one from reserve
   CheckersMove::LocVector::iterator itr = tm->mLocs.begin();

   PutMarble(&mSpots[itr->first][itr->second]);

   itr++;
   for (; itr != tm->mLocs.end(); itr++) {
      TakeMarble(&mSpots[itr->first][itr->second]);
      rChange++;
   }

   if (mWhoseMove == kWhite)
      mWhiteReserve += rChange;
   else
      mBlackReserve += rChange;
   assert(mWhiteReserve >= 0);
   assert(mBlackReserve >= 0);

   mMoveHist.push_back(move);
   mWhoseMove = -mWhoseMove;
   */
}

void CheckersBoard::UndoLastMove()
{
   /*
   int rChange = 1; // Start by assuming we'll gain one to reserve.
   CheckersMove* lastMove = dynamic_cast<CheckersMove *>(mMoveHist.back());
   mMoveHist.pop_back();

   mWhoseMove = -mWhoseMove;

   CheckersMove::LocVector::iterator itr = lastMove->mLocs.end()-1;
   for (; itr != lastMove->mLocs.begin(); itr--) {
      PutMarble(&mSpots[itr->first][itr->second]);
      rChange--;
   }
   TakeMarble(&mSpots[itr->first][itr->second]);

   if (mWhoseMove == kWhite)
      mWhiteReserve += rChange;
   else
      mBlackReserve += rChange;

   delete lastMove;
   */
}

void CheckersBoard::GetAllMoves(std::list<Move *> *moves) const
{
   /*
   int tRow, tCol, sRow, sCol;
   Cell *trg, *src;
   CheckersMove::LocVector locs;
   std::list<CheckersMove *>::iterator itr;
   std::list<CheckersMove *> *mvs = reinterpret_cast<
    std::list<CheckersMove *>*>(moves);
   ulong sideMask = mWhoseMove == kWhite ? mWhite : mBlack;

   moves->clear();
   if (mWhiteReserve == 0 || mBlackReserve == 0)
      return;

   for (tRow = 0; tRow < kDim; tRow++) {
      for (tCol = 0; tCol < kDim; tCol++) {
         trg = mSpots[tRow][tCol].empty;
         if (trg && (trg->subs & (mWhite|mBlack)) == trg->subs) { // found a target spot
            locs.clear();
            locs.push_back(std::pair<int, int>(tRow, tCol));
            moves->push_back(new CheckersMove(locs, CheckersMove::kReserve));

            for (sRow = 0; sRow < kDim; sRow++) { // search for promote moves
               for (sCol = 0; sCol < kDim; sCol++) {
                  src = mSpots[sRow][sCol].top;
                  if (src && (src->sups & (mWhite|mBlack)) == 0
                   && (src->mask & sideMask) && src->level < trg->level
                   && (sRow < tRow || sRow > tRow + 1    // Not a support for trg
                   || sCol < tCol || sCol > tCol + 1)) {
                     locs.push_back(std::pair<int, int>(sRow, sCol));
                     moves->push_back(new CheckersMove(locs, CheckersMove::kPromote));
                     locs.pop_back();
                  }
               }
            }
         }
      }
   }

   AddTakeBacks(mvs);
   */
}

void CheckersBoard::HalfApplyMove(CheckersMove *pm) const {
   /*
   CheckersMove::LocVector::iterator iter = pm->mLocs.begin();
   HalfPut(&mSpots[iter->first][iter->second]);
   for (++iter; iter != pm->mLocs.end(); iter++)
      HalfTake(&mSpots[iter->first][iter->second]);
      */
}

void CheckersBoard::UnHalfApplyMove(CheckersMove *pm) const {
   /*
   CheckersMove::LocVector::iterator iter = pm->mLocs.end()-1;
   for (; iter != pm->mLocs.begin(); iter--)
      HalfPut(&mSpots[iter->first][iter->second]);
   HalfTake(&mSpots[iter->first][iter->second]);
   */
}

Board::Move *CheckersBoard::CreateMove() const
{
   return NULL;
   //return new CheckersMove(CheckersMove::LocVector(1), CheckersMove::kReserve);
}

Board *CheckersBoard::Clone() const
{
   return NULL;
}

Board::Key *CheckersBoard::GetKey() const
{
   /*
   BasicKey<2> *rtn = dynamic_cast<BasicKey<2> *>(BasicKey<2>::Create());

   rtn->vals[0] = (mWhoseMove == kWhite) << kNumCells | mWhite;
   rtn->vals[1] = mBlack;

   return rtn;
   */
   return NULL;
}

std::istream &CheckersBoard::Read(std::istream &is)
{
   /*
   Move *tempMove;
   int mvCount = 0;

   Delete();
   mMoveHist.clear();
   Init();

   is.read((char *)&mRules, sizeof(Rules));
   mRules.EndSwap();

   is.read((char *)&mvCount, sizeof(int));
   mvCount = EndianXfer(mvCount);
   for (int i = 0; i < mvCount; i++) {
      tempMove = CreateMove();
      is >> *dynamic_cast<CheckersMove *>(tempMove);
      ApplyMove(tempMove);
   }
   */

   return is;
}

// Don't change this.  Make Read conform to it.
std::ostream &CheckersBoard::Write(std::ostream &os) const
{
   /*
   Rules rls = mRules;
   std::list<Move *>::const_iterator itr;
   int mvCount = EndianXfer((int)mMoveHist.size());

   rls.EndSwap();
   os.write((char *)&rls, sizeof(rls));

   os.write((char *)&mvCount, sizeof(mvCount));
   for (itr = mMoveHist.begin(); itr != mMoveHist.end(); itr++)
      os << **itr;
   */

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
   mRules = *reinterpret_cast<const Rules *>(opts);
}

void CheckersBoard::Delete()
{
   for (std::list<Move *>::iterator iter = mMoveHist.begin();
         iter != mMoveHist.end(); iter++) {
      delete *iter;
   }
}
