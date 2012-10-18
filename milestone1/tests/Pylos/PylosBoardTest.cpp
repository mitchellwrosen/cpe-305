
#include "../../PylosMove.h"
#include "../Test.h"

#include <fstream>
#include <iostream>
#include <vector>

class PylosMoveTest : public Test {
public:
   typedef std::vector<std::pair<short, short> > LocVector;

   TEST(NewDelete) {
      assert(PylosMove::mFreeList.size() == 0);
      assert(PylosMove::mOutstanding == 0);

      LocVector locs;
      PylosMove *pm1 = new PylosMove(locs, PylosMove::kReserve);
      PylosMove *pm2 = new PylosMove(locs, PylosMove::kReserve);
      assert(PylosMove::mOutstanding == 2);

      delete pm1;
      assert(PylosMove::mFreeList.size() == 1);
      assert(PylosMove::mOutstanding == 1);

      delete pm2;
      assert(PylosMove::mFreeList.size() == 2);
      assert(PylosMove::mOutstanding == 0);
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

   TEST(OperatorString) {
      // Play.
      LocVector locs;
      locs.push_back(std::make_pair(0,0));
      PylosMove pm(locs, PylosMove::kReserve);
      assert((std::string) pm == "Play at [0, 0]");

      // Play taking.
      locs.push_back(std::make_pair(1,1));
      pm = PylosMove(locs, PylosMove::kReserve);
      assert((std::string) pm == "Play at [0, 0] taking [1, 1]");

      // Promote from.
      pm = PylosMove(locs, PylosMove::kPromote);
      assert((std::string) pm == "Promote from [0, 0] to [1, 1]");

      // Play taking and.
      locs.push_back(std::make_pair(2,2));
      pm = PylosMove(locs, PylosMove::kReserve);
      assert((std::string) pm == "Play at [0, 0] taking [1, 1] and [2, 2]");

      // Promote from taking.
      pm = PylosMove(locs, PylosMove::kPromote);
      assert((std::string) pm == "Promote from [0, 0] to [1, 1] taking [2, 2]");

      // Promote from taking and.
      locs.push_back(std::make_pair(3, 3));
      pm = PylosMove(locs, PylosMove::kPromote);
      assert((std::string) pm == "Promote from [0, 0] to [1, 1] taking [2, 2] and [3, 3]");
   }

   TEST(OperatorEq) {
      // TODO
   }

   TEST(Clone) {
      LocVector locs;
      PylosMove pm1(locs, PylosMove::kReserve);
      PylosMove *pm2 = dynamic_cast<PylosMove *>(pm1.Clone());
      assert(pm1 == *pm2);
   }

   TEST(ReadWrite) {
      LocVector locs;
      PylosMove pm1(locs, PylosMove::kReserve);

      locs.push_back(std::make_pair(0,0));
      locs.push_back(std::make_pair(1,1));
      locs.push_back(std::make_pair(2,2));
      locs.push_back(std::make_pair(3,3));
      PylosMove pm2(locs, PylosMove::kPromote);

      std::filebuf fb;
      fb.open("PylosMove.out", std::ios::out);
      std::ostream os(&fb);
      pm2.Write(os);
      fb.close();

      fb.open("PylosMove.out", std::ios::in);
      std::istream is(&fb);
      pm1.Read(is);
      fb.close();

      assert(pm1 == pm2);
   }

   PylosMoveTest() {
      ADD_TEST(NewDelete);
      ADD_TEST(OperatorEqEq);
      ADD_TEST(OperatorLessThan);
      ADD_TEST(OperatorString);
      //ADD_TEST(OperatorEq);
      ADD_TEST(Clone);
      ADD_TEST(ReadWrite);
   }
};

RUN_TEST(PylosMoveTest);
