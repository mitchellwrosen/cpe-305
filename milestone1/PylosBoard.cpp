#include <assert.h>
#include <memory.h>
#include <limits.h>
#include "Class.h"
#include "PylosDlg.h"
#include "PylosBoard.h"
#include "PylosMove.h"
#include "PylosView.h"
#include "BasicKey.h"

// static
PylosBoard::Set PylosBoard::mSets[kNumSets];

// static
PylosBoard::Cell PylosBoard::mCells[kNumCells];

// static
int PylosBoard::mOffs[kDim] = {0, 16, 25, 29};

// static
PylosBoard::StaticInitializer PylosBoard::staticInitializer;

// static
BoardClass PylosBoard::mClass = BoardClass("PylosBoard", &PylosBoard::Create,
 "Pylos", PylosView::GetClassPtr(), PylosDlg::GetClassPtr(),
 &PylosBoard::GetOptions, &PylosBoard::SetOptions);

// static
void PylosBoard::StaticInit()
{
   Cell *cell;
   int setNdx;

   for (int i = 0; i < kNumCells; i++)
      mCells[i] = Cell();
   for (int i = 0; i < kNumSets; i++)
      mSets[i] = 0;

   for (int level = 0, nextCell = 0; level < kDim; level++) {
      for (int row = 0; row < kDim - level; row++) {
         for (int col = 0; col < kDim - level; col++, nextCell++) {
            cell = mCells + nextCell;
            cell->level = level;
            cell->mask = 1 << nextCell;

            // Set up below and above pointers.
            cell->above = NULL;
            if (level > 0) {
               cell->below[kNW] = GetCell(row, col, level-1);
               cell->below[kNE] = GetCell(row, col+1, level-1);
               cell->below[kSE] = GetCell(row+1, col+1, level-1);
               cell->below[kSW] = GetCell(row+1, col, level-1);

               for (int ndx = 0; ndx < kSqr; ndx++) {
                  cell->below[ndx]->sups |= cell->mask;
                  cell->subs |= cell->below[ndx]->mask;
               }

               cell->below[kNW]->above = cell;
            }

            if (level < 2) {
               // The last row -- create vertical set.
               if (row == kDim - level - 1) {
                  setNdx = 18 + col + 7*level;
                  for (int ndx = 0; ndx < kDim - level; ndx++) {
                     mSets[setNdx] |=
                      (mCells + nextCell - ndx*(4-level))->mask;
                  }

                  for (int ndx = 0; ndx < kDim - level; ndx++) {
                     (mCells + nextCell - ndx*(4-level))->
                      addSet(mSets[setNdx]);
                  }
               }

               // The last column in a row -- create horizontal set.
               if (col == kDim - level - 1) {
                  setNdx = 14 + row + 8*level;
                  for (int ndx = 0; ndx < kDim - level; ndx++)
                     mSets[setNdx] |= (mCells + nextCell - ndx)->mask;
                  for (int ndx = 0; ndx < kDim - level; ndx++)
                     (mCells + nextCell - ndx)->addSet(mSets[setNdx]);
               }
            }
         }
      }
   }

   AddSquareSets();
}

// static
void PylosBoard::AddSquareSets()
{
   for (int level = 0, nextCell = 0; level < kDim - 1; level++) {
      for (int row = 0; row < kDim - level - 1; row++) {
         for (int col = 0; col < kDim - level - 1; col++, nextCell++) {
            mSets[nextCell] |= GetCell(row, col, level)->mask;
            mSets[nextCell] |= GetCell(row, col+1, level)->mask;
            mSets[nextCell] |= GetCell(row+1, col, level)->mask;
            mSets[nextCell] |= GetCell(row+1, col+1, level)->mask;

            GetCell(row, col, level)->addSet(mSets[nextCell]);
            GetCell(row, col+1, level)->addSet(mSets[nextCell]);
            GetCell(row+1, col, level)->addSet(mSets[nextCell]);
            GetCell(row+1, col+1, level)->addSet(mSets[nextCell]);
         }
      }
   }
}

void PylosBoard::Rules::SetMarble(int val)
{
   if (val < 1 || val > 1000)
      throw BaseException("Marble weight must be between 1 and 1000 inclusive");

   marbleWgt = val;
}

void PylosBoard::Rules::SetLevel(int val)
{
   if (val >= marbleWgt || val < 0)
      throw BaseException("Level weight must be nonnegative and less than"
       " marble weight");

   levelWgt = val;
}

void PylosBoard::Rules::SetFree(int val)
{
   if (val % 2 != 0 || val < 0 || val >= marbleWgt)
      throw BaseException("Free weight must be even, nonnegative, and less"
       " than marble weight");

   freeWgt = val;
}

void PylosBoard::Rules::EndSwap()
{
   levelWgt = EndianXfer(levelWgt);
   freeWgt = EndianXfer(freeWgt);
   marbleWgt = EndianXfer(marbleWgt);
}

PylosBoard::PylosBoard()
{
   Init();
}

void PylosBoard::Init()
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

PylosBoard::Rules PylosBoard::mRules;

long PylosBoard::GetValue() const
{
   if (mWhiteReserve == 0)
      return -kWinVal;
   else if (mBlackReserve == 0)
      return kWinVal;
   else
      return mRules.marbleWgt*(mWhiteReserve - mBlackReserve)
       + mRules.levelWgt * mLevelLead + mRules.freeWgt * mFreeLead;
}

void PylosBoard::PutMarble(Spot *trg)
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

void PylosBoard::TakeMarble(Spot *trg)
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

void PylosBoard::ApplyMove(Move *move)
{
   PylosMove *tm = dynamic_cast<PylosMove *>(move);
   int rChange = -1;  // Start by assuming we'll lose one from reserve
   PylosMove::LocVector::iterator itr = tm->mLocs.begin();

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

void PylosBoard::UndoLastMove()
{
   int rChange = 1; // Start by assuming we'll gain one to reserve.
   PylosMove* lastMove = dynamic_cast<PylosMove *>(mMoveHist.back());
   mMoveHist.pop_back();

   mWhoseMove = -mWhoseMove;

   PylosMove::LocVector::iterator itr = lastMove->mLocs.end()-1;
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

void PylosBoard::GetAllMoves(std::list<Move *> *moves) const
{
   int tRow, tCol, sRow, sCol;
   Cell *trg, *src;
   PylosMove::LocVector locs;
   std::list<PylosMove *>::iterator itr;
   std::list<PylosMove *> *mvs = reinterpret_cast<
    std::list<PylosMove *>*>(moves);
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
            moves->push_back(new PylosMove(locs, PylosMove::kReserve));

            for (sRow = 0; sRow < kDim; sRow++) { // search for promote moves
               for (sCol = 0; sCol < kDim; sCol++) {
                  src = mSpots[sRow][sCol].top;
                  if (src && (src->sups & (mWhite|mBlack)) == 0
                   && (src->mask & sideMask) && src->level < trg->level
                   && (sRow < tRow || sRow > tRow + 1    // Not a support for trg
                   || sCol < tCol || sCol > tCol + 1)) {
                     locs.push_back(std::pair<int, int>(sRow, sCol));
                     moves->push_back(new PylosMove(locs, PylosMove::kPromote));
                     locs.pop_back();
                  }
               }
            }
         }
      }
   }

   AddTakeBacks(mvs);
}

void PylosBoard::HalfApplyMove(PylosMove *pm) const {
   PylosMove::LocVector::iterator iter = pm->mLocs.begin();
   HalfPut(&mSpots[iter->first][iter->second]);
   for (++iter; iter != pm->mLocs.end(); iter++)
      HalfTake(&mSpots[iter->first][iter->second]);
}

void PylosBoard::UnHalfApplyMove(PylosMove *pm) const {
   PylosMove::LocVector::iterator iter = pm->mLocs.end()-1;
   for (; iter != pm->mLocs.begin(); iter--)
      HalfPut(&mSpots[iter->first][iter->second]);
   HalfTake(&mSpots[iter->first][iter->second]);
}

bool PylosBoard::PartOfAlignment(std::pair<short, short> &pr) const {
   Cell *cell = mSpots[pr.first][pr.second].top;
   ulong sideMask = mWhoseMove == kWhite ? mWhite : mBlack;

   for (int i = 0; i < cell->setCount; i++)
      if ((sideMask & cell->sets[i]) == cell->sets[i])
         return true;
   return false;
}

bool PylosBoard::CanTakeback(Spot *spot) const {
   ulong sideMask = mWhoseMove == kWhite ? mWhite : mBlack;
   if (spot->top && (spot->top->mask & sideMask) &&
        (spot->top->sups & (mWhite | mBlack)) == 0) {
      return true;
   }
   return false;
}

// For each move in *mvs that completes one or more sets, add all
// combination of spots to take back.
void PylosBoard::AddTakeBacks(std::list<PylosMove *> *mvs) const
{
   int numMoves = mvs->size();
   PylosMove::LocVector locs;
   PylosMove *move;
   Spot *spot1, *spot2;
   for (std::list<PylosMove *>::iterator iter = mvs->begin(); numMoves > 0;
    numMoves--) {
      move = *iter;
      iter++;
      HalfApplyMove(move);
      if (PartOfAlignment(move->mLocs[0])) {
         for (short row1 = 0; row1 < kDim; row1++) {
            for (short col1 = 0; col1 < kDim; col1++) {
               spot1 = &mSpots[row1][col1];
               if (CanTakeback(spot1)) {
                  HalfTake(spot1);
                  locs = move->mLocs;
                  locs.push_back(std::make_pair(row1, col1));

                  mvs->insert(iter, new PylosMove(locs, move->mType));

                  for (short row2 = row1; row2 < kDim; row2++) {
                     for (short col2 = 0; col2 < kDim; col2++) {
                        if (row2 == row1 && col2 < col1)
                           continue;
                        spot2 = &mSpots[row2][col2];
                        if (CanTakeback(spot2)) {
                           //HalfTake(spot2);
                           locs.push_back(std::make_pair(row2, col2));
                           mvs->insert(iter, new PylosMove(locs, move->mType));
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

Board::Move *PylosBoard::CreateMove() const
{
   return new PylosMove(PylosMove::LocVector(1), PylosMove::kReserve);
}

Board *PylosBoard::Clone() const
{
   PylosBoard *pb = new PylosBoard();
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

const Board::Key *PylosBoard::GetKey() const
{
   BasicKey<2> *rtn = dynamic_cast<BasicKey<2> *>(BasicKey<2>::Create());

   rtn->vals[0] = (mWhoseMove == kWhite) << kNumCells | mWhite;
   rtn->vals[1] = mBlack;

   return rtn;
}

std::istream &PylosBoard::Read(std::istream &is)
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
      is >> *dynamic_cast<PylosMove *>(tempMove);
      ApplyMove(tempMove);
   }

   return is;
}

std::ostream &PylosBoard::Write(std::ostream &os) const
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

const Class *PylosBoard::GetClass() const
{
   return &mClass;
}

// static
Object *PylosBoard::Create()
{
   return new PylosBoard();
}

// static
void *PylosBoard::GetOptions()
{
   return new Rules(mRules);
}

// static
void PylosBoard::SetOptions(const void *opts)
{
   mRules = *reinterpret_cast<const Rules *>(opts);
}

void PylosBoard::Delete()
{
   for (std::list<Move *>::iterator iter = mMoveHist.begin();
         iter != mMoveHist.end(); iter++) {
      delete *iter;
   }
}
