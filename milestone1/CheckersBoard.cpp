#include <assert.h>
#include <memory.h>
#include <limits.h>
#include "Class.h"
//#include "CheckersDlg.h"
#include "CheckersBoard.h"
//#include "CheckersMove.h"
//#include "CheckersView.h"
#include "BasicKey.h"

// static
CheckersBoard::Cell CheckersBoard::mCells[kNumCells] = {
Cell(0,0),Cell(0,1),Cell(0,2),Cell(0,3),Cell(0,4),Cell(0,5),Cell(0,6),Cell(0,7),
Cell(1,0),Cell(1,1),Cell(1,2),Cell(1,3),Cell(1,4),Cell(1,5),Cell(1,6),Cell(1,7),
Cell(2,0),Cell(2,1),Cell(1,2),Cell(1,3),Cell(1,4),Cell(1,5),Cell(1,6),Cell(1,7),
Cell(3,0),Cell(3,1),Cell(3,2),Cell(3,3),Cell(3,4),Cell(3,5),Cell(3,6),Cell(3,7),
Cell(4,0),Cell(4,1),Cell(4,2),Cell(4,3),Cell(4,4),Cell(4,5),Cell(4,6),Cell(4,7),
Cell(5,0),Cell(5,1),Cell(5,2),Cell(5,3),Cell(5,4),Cell(5,5),Cell(5,6),Cell(5,7),
Cell(6,0),Cell(6,1),Cell(6,2),Cell(6,3),Cell(6,4),Cell(6,5),Cell(6,6),Cell(6,7),
Cell(7,0),Cell(7,1),Cell(7,2),Cell(7,3),Cell(7,4),Cell(7,5),Cell(7,6),Cell(7,7)
};

// static
BoardClass CheckersBoard::mClass = BoardClass("CheckersBoard", 
 &CheckersBoard::Create, "Checkers", "CheckersView", "CheckersDlg", 
 &CheckersBoard::GetOptions, &CheckersBoard::SetOptions);

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

CheckersBoard::CheckersBoard()
{
   Init();
}

void CheckersBoard::Init()
{
   mWhite = mBlack = mLevelLead = mFreeLead = 0;
   mWhoseMove = kWhite;
   mWhiteReserve = mBlackReserve = kStones;
   for (int row = 0; row < kDim; row++) {
      for (int col = 0; col < kDim; col++) {
         mSpots[row][col].top = NULL;
         mSpots[row][col].empty = mCells + row*kDim + col;
      }
   }
}

CheckersBoard::Rules CheckersBoard::mRules;

long CheckersBoard::GetValue() const
{
   if (mWhiteReserve == 0)
      return -kWinVal;
   else if (mBlackReserve == 0)
      return kWinVal;
   else
      return mRules.marbleWgt*(mWhiteReserve - mBlackReserve)
       + mRules.levelWgt * mLevelLead + mRules.freeWgt * mFreeLead;
}

void CheckersBoard::PutMarble(Spot *trg)
{
   assert(trg->empty);

   mLevelLead += mWhoseMove * trg->empty->level;
   mFreeLead += mWhoseMove; // Newly placed marble is free.
   // Belows are no longer free, if they were before.
   if (trg->empty->level != 0) {
      for (int i = 0; i < kSqr; i++) {
         if (!(trg->empty->below[i]->sups & (mWhite|mBlack)))
            mFreeLead -= trg->empty->below[i]->mask & mWhite ? kWhite : kBlack;
      }
   }

   HalfPut(trg);
}

void CheckersBoard::TakeMarble(Spot *trg)
{
   assert(trg->top);

   HalfTake(trg);

   mLevelLead -= mWhoseMove * trg->empty->level;
   mFreeLead -= mWhoseMove; // Removed marble is no longer free.
   // Belows now may be free.
   if (trg->empty->level != 0) {
      for (int i = 0; i < kSqr; i++) {
         if (!(trg->empty->below[i]->sups & (mWhite|mBlack)))
            mFreeLead += trg->empty->below[i]->mask & mWhite ? kWhite : kBlack;
      }
   }
}

void CheckersBoard::ApplyMove(Move *move)
{
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
}

void CheckersBoard::UndoLastMove()
{
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
}

void CheckersBoard::GetAllMoves(std::list<Move *> *moves) const
{
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
}

void CheckersBoard::HalfApplyMove(CheckersMove *pm) const {
   CheckersMove::LocVector::iterator iter = pm->mLocs.begin();
   HalfPut(&mSpots[iter->first][iter->second]);
   for (++iter; iter != pm->mLocs.end(); iter++)
      HalfTake(&mSpots[iter->first][iter->second]);
}

void CheckersBoard::UnHalfApplyMove(CheckersMove *pm) const {
   CheckersMove::LocVector::iterator iter = pm->mLocs.end()-1;
   for (; iter != pm->mLocs.begin(); iter--)
      HalfPut(&mSpots[iter->first][iter->second]);
   HalfTake(&mSpots[iter->first][iter->second]);
}

bool CheckersBoard::PartOfAlignment(std::pair<short, short> &pr) const {
   Cell *cell = mSpots[pr.first][pr.second].top;
   ulong sideMask = mWhoseMove == kWhite ? mWhite : mBlack;

   for (int i = 0; i < cell->setCount; i++)
      if ((sideMask & cell->sets[i]) == cell->sets[i])
         return true;
   return false;
}

bool CheckersBoard::CanTakeback(Spot *spot) const {
   ulong sideMask = mWhoseMove == kWhite ? mWhite : mBlack;
   if (spot->top && (spot->top->mask & sideMask) &&
        (spot->top->sups & (mWhite | mBlack)) == 0) {
      return true;
   }
   return false;
}

// For each move in *mvs that completes one or more sets, add all
// combination of spots to take back.
void CheckersBoard::AddTakeBacks(std::list<CheckersMove *> *mvs) const
{
   ulong sideMask = mWhoseMove == kWhite ? mWhite : mBlack;
   int numMoves = mvs->size();
   CheckersMove::LocVector locs;
   CheckersMove *move;
   Spot *spot1, *spot2;
   for (std::list<CheckersMove *>::iterator iter = mvs->begin(); numMoves > 0;
    numMoves--, iter++) {
      move = *iter;
      HalfApplyMove(move);
      if (PartOfAlignment(move->mLocs[0])) {
         for (short row1 = 0; row1 < kDim; row1++) {
            for (short col1 = 0; col1 < kDim; col1++) {
               spot1 = &mSpots[row1][col1];
               if (CanTakeback(spot1)) {
                  HalfTake(spot1);
                  locs = move->mLocs;
                  locs.push_back(std::make_pair(row1, col1));
                  mvs->push_back(new CheckersMove(locs, move->mType));

                  for (short row2 = row1; row2 < kDim; row2++) {
                     for (short col2 = 0; col2 < kDim; col2++) {
                        if (row2 == row1 && col2 < col1)
                           continue;
                        spot2 = &mSpots[row2][col2];
                        if (CanTakeback(spot2)) {
                           //HalfTake(spot2);
                           locs.push_back(std::make_pair(row2, col2));
                           mvs->push_back(new CheckersMove(locs, move->mType));
                           locs.pop_back();
                           //HalfPut(spot2);
                        }
                     }
                  }
                  HalfPut(spot1);
               }
            }
         }
      }
      UnHalfApplyMove(move);
   }
}

Board::Move *CheckersBoard::CreateMove() const
{
   return new CheckersMove(CheckersMove::LocVector(1), CheckersMove::kReserve);
}

Board *CheckersBoard::Clone() const
{
   // Think carefully about this one.  You should be able to do it in just
   // 5-10 lines.  Don't do needless work
   CheckersBoard *pb = new CheckersBoard();
   pb->mWhite = mWhite;
   pb->mBlack = mBlack;
   pb->mWhoseMove = mWhoseMove;
   pb->mWhiteReserve = mWhiteReserve;
   pb->mBlackReserve = mBlackReserve;
   pb->mFreeLead = mFreeLead;
   for (std::list<Move *>::const_iterator iter = mMoveHist.begin();
         iter != mMoveHist.end(); iter++) {
      pb->mMoveHist.push_back((*iter)->Clone());
   }
   return pb;
}

Board::Key *CheckersBoard::GetKey() const
{
   BasicKey<2> *rtn = dynamic_cast<BasicKey<2> *>(BasicKey<2>::Create());

   rtn->vals[0] = (mWhoseMove == kWhite) << kNumCells | mWhite;
   rtn->vals[1] = mBlack;

   return rtn;
}

std::istream &CheckersBoard::Read(std::istream &is)
{
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

   return is;
}

// Don't change this.  Make Read conform to it.
std::ostream &CheckersBoard::Write(std::ostream &os) const
{
   Rules rls = mRules;
   std::list<Move *>::const_iterator itr;
   int mvCount = EndianXfer((int)mMoveHist.size());

   rls.EndSwap();
   os.write((char *)&rls, sizeof(rls));

   os.write((char *)&mvCount, sizeof(mvCount));
   for (itr = mMoveHist.begin(); itr != mMoveHist.end(); itr++)
      os << **itr;

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
