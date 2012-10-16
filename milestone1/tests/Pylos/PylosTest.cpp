
#include "../../PylosMove.h"
#include "../Test.h"

#include <vector>

class PylosTest : public Test {
public:
   typedef std::vector<std::pair<short, short> > LocVector;

   TEST(NewDelete) {
   }

   TEST(OperatorEqEq) {
      // Compare {Reserve (0,0), (1,1)} with itself.
      LocVector locs1, locs2;
      locs1.push_back(std::make_pair(0,0));
      locs1.push_back(std::make_pair(1,1));
      locs2.push_back(std::make_pair(0,0));
      locs2.push_back(std::make_pair(1,1));
      PylosMove move1(locs1, PylosMove::kReserve);
      PylosMove move2(locs2, PylosMove::kReserve);
      assert(move1 == move2);

      // Compare {Reserve (0,0), (1,1)} with {Promote (0,0), (1,1)}
      move2 = PylosMove(locs2, PylosMove::kPromote);
      assert(!(move1 == move2));

      // Compare {Reserve (0,0), (1,1)} with {Reserve (0,0), (1,1), (2,2)}
      locs2.push_back(std::make_pair(2,2));
      move2 = PylosMove(locs2, PylosMove::kReserve);
      assert(!(move1 == move2));
   }

   TEST(OperatorLessThan) {
      // Compare {Reserve (0,0)} with itself.
      LocVector locs1, locs2;
      locs1.push_back(std::make_pair(0,0));
      locs2.push_back(std::make_pair(0,0));
      PylosMove move1(locs1, PylosMove::kReserve);
      PylosMove move2(locs2, PylosMove::kReserve);
      assert(!(move1 < move2));

      // Compare {Reserve (0,0)} with {Promote (0,0)}
      move2 = PylosMove(locs2, PylosMove::kPromote);
      assert(move1 < move2);

      // Compare {Reserve (0,0)} with {Reserve (0,0), (1,1)}
      locs2.push_back(std::make_pair(1,1));
      move2 = PylosMove(locs2, PylosMove::kReserve);
      assert(move1 < move2);

      // Compare {Reserve (0,0), (1,1)} with {Reserve (0,0), (1,1)}
      locs1.push_back(std::make_pair(1,1));
      move1 = PylosMove(locs1, PylosMove::kReserve);
      assert(!(move1 < move2));

      // Compare {Reserve (0,0), (1,1)} with {Reserve (0,0), (1,1), (2,2)}
      locs2.push_back(std::make_pair(2,2));
      move2 = PylosMove(locs2, PylosMove::kReserve);
      assert(move1 < move2);
   }

   PylosTest() {
      ADD_TEST(NewDelete);
      ADD_TEST(OperatorEqEq);
      ADD_TEST(OperatorLessThan);
   }
};

int main() {
   PylosTest test;
   test.Run();
}
