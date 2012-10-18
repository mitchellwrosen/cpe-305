
#include "../../PylosMove.h"
#include "../Test.h"

#include <fstream>
#include <iostream>
#include <vector>

class PylosBoardTest : public Test {
public:
   TEST(StaticInit) {
      for (int level = 0, nextCell = 0; level < PylosBoard::kDim; level++) {
         for (int row = 0; row < PylosBoard::kDim; row++) {
            for (int col = 0; col < PylosBoard::kDim; col++, nextCell++) {
               assert(PylosBoard::mCells[nextCell].mask == 1 << nextCell);
            }
         }
      }
   }

   PylosBoardTest() {
      ADD_TEST(StaticInit);
   }
};

RUN_TEST(PylosBoardTest);
