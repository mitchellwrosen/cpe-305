
#include "../../PylosMove.h"
#include "../Test.h"

#include <fstream>
#include <iostream>
#include <vector>

class PylosBoardTest : public Test {
public:
   TEST(StaticInit) {
      for (int level = 0, nextCell = 0; level < PylosBoard::kDim; level++) {
         for (int row = 0; row < PylosBoard::kDim - level; row++) {
            for (int col = 0; col < PylosBoard::kDim - level; col++, nextCell++) {
               PylosBoard::Cell *curCell = PylosBoard::mCells + nextCell;

               assert(curCell->level == level);
               assert(curCell->mask == 1 << nextCell);

               ulong mask = 0;
               if (level > 0) {
                  mask = curCell->below[PylosBoard::kNW]->mask |
                         curCell->below[PylosBoard::kNE]->mask |
                         curCell->below[PylosBoard::kSW]->mask |
                         curCell->below[PylosBoard::kSE]->mask;
               }
               assert(curCell->subs == mask);

               mask = 0;
               if (level < PylosBoard::kDim-1) {
                  if (row < PylosBoard::kDim-level-1 &&
                       col < PylosBoard::kDim-level-1) {
                     mask |= curCell->above->mask;
                  }
                  if (row < PylosBoard::kDim-level-1 && col > 0)
                     mask |= PylosBoard::GetCell(row, col-1, level+1)->mask;
                  if (row > 0 && col < PylosBoard::kDim-level-1)
                     mask |= PylosBoard::GetCell(row-1, col, level+1)->mask;
                  if (row > 0 && col > 0)
                     mask |= PylosBoard::GetCell(row-1, col-1, level+1)->mask;
               }
               assert(curCell->sups == mask);

               int setCount = 0;
               if (level < 2)
                  setCount += 2; // Vertical, horizontal
               if (row < PylosBoard::kDim-level-1 &&
                    col < PylosBoard::kDim-level-1) {
                  setCount++;
               }
               if (row < PylosBoard::kDim-level-1 && col > 0)
                  setCount++;
               if (row > 0 && col < PylosBoard::kDim-level-1)
                  setCount++;
               if (row > 0 && col > 0)
                  setCount++;
               AssertEq(curCell->setCount, setCount);
            }
         }
      }
   }

   PylosBoardTest() {
      ADD_TEST(StaticInit);
   }
};

RUN_TEST(PylosBoardTest);
