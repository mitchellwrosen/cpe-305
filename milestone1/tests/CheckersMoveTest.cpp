#include "gtest/include/gtest/gtest.h"
#include "../MyLib.h"
#include "../CheckersBoard.h"
#include "../CheckersMove.h"

/*
TEST(CheckersMoveTest, OperatorEqualsEquals) {
   CheckersMove::LocVector locs1, locs2;

   locs1.push_back(std::make_pair(0, 0));
   locs2.push_back(std::make_pair(0, 0));
   EXPECT_TRUE(CheckersMove(locs1) == CheckersMove(locs2));

   locs2.push_back(std::make_pair(1, 1));
   EXPECT_FALSE(CheckersMove(locs1) == CheckersMove(locs2));
}

TEST(CheckersMoveTest, OperatorEquals) {
   CheckersMove move(CheckersMove::LocVector(1));

   move = "A1 -> A2";
   EXPECT_EQ(CheckersMove::kMove, move.mType);
   ASSERT_EQ(2U, move.mLocs.size());
   EXPECT_EQ(0, move.mLocs[0].first);
   EXPECT_EQ(0, move.mLocs[0].second);
   EXPECT_EQ(0, move.mLocs[1].first);
   EXPECT_EQ(1, move.mLocs[1].second);

   move = "A1->A2";
   EXPECT_EQ(CheckersMove::kMove, move.mType);
   ASSERT_EQ(2U, move.mLocs.size());
   EXPECT_EQ(0, move.mLocs[0].first);
   EXPECT_EQ(0, move.mLocs[0].second);
   EXPECT_EQ(0, move.mLocs[1].first);
   EXPECT_EQ(1, move.mLocs[1].second);

   move = "a1->a2";
   EXPECT_EQ(CheckersMove::kMove, move.mType);
   ASSERT_EQ(2U, move.mLocs.size());
   EXPECT_EQ(0, move.mLocs[0].first);
   EXPECT_EQ(0, move.mLocs[0].second);
   EXPECT_EQ(0, move.mLocs[1].first);
   EXPECT_EQ(1, move.mLocs[1].second);

   move = "a 1 -> a 2";
   EXPECT_EQ(CheckersMove::kMove, move.mType);
   ASSERT_EQ(2U, move.mLocs.size());
   EXPECT_EQ(0, move.mLocs[0].first);
   EXPECT_EQ(0, move.mLocs[0].second);
   EXPECT_EQ(0, move.mLocs[1].first);
   EXPECT_EQ(1, move.mLocs[1].second);

   try {
      move = "A1->A2 foo";
      EXPECT_TRUE(false);
   } catch (BaseException e) {
   }

   try {
      move = "A1 - > a2";
   } catch (BaseException e) {
   }

   move = "A1 -> A2 -> A3";
   EXPECT_EQ(CheckersMove::kCapture, move.mType);
   ASSERT_EQ(3U, move.mLocs.size());
   EXPECT_EQ(0, move.mLocs[0].first);
   EXPECT_EQ(0, move.mLocs[0].second);
   EXPECT_EQ(0, move.mLocs[1].first);
   EXPECT_EQ(1, move.mLocs[1].second);
   EXPECT_EQ(0, move.mLocs[2].first);
   EXPECT_EQ(2, move.mLocs[2].second);

   move = "a1->a2->a3";
   EXPECT_EQ(CheckersMove::kCapture, move.mType);
   ASSERT_EQ(3U, move.mLocs.size());
   EXPECT_EQ(0, move.mLocs[0].first);
   EXPECT_EQ(0, move.mLocs[0].second);
   EXPECT_EQ(0, move.mLocs[1].first);
   EXPECT_EQ(1, move.mLocs[1].second);
   EXPECT_EQ(0, move.mLocs[2].first);
   EXPECT_EQ(2, move.mLocs[2].second);

   try {
      move = "a1->a2->A3 foo";
      EXPECT_TRUE(false);
   } catch (BaseException e) {
   }
}
*/
