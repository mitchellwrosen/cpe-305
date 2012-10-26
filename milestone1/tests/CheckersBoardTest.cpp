#include "gtest/include/gtest/gtest.h"
#include "../CheckersBoard.h"
#include "../CheckersMove.h"

/*
TEST(CheckersBoardTest, Init) {
   CheckersBoard board;

   uint64_t mask = 1;
   for (int row = 0; row < CheckersBoard::kDim; row++) {
      for (int col = 0; col < CheckersBoard::kDim; col++, mask <<= 1) {
         const CheckersBoard::Cell *cell = board.GetCell(row, col);
         EXPECT_EQ(cell->row, row);
         EXPECT_EQ(cell->col, col);
         EXPECT_EQ(cell->mask, mask);
         if (cell->piece) {
            EXPECT_EQ(cell->piece->row, cell->row);
            EXPECT_EQ(cell->piece->col, cell->col);
            EXPECT_EQ(cell->piece->rank, CheckersBoard::kRegular);

            if (cell->piece->whose == CheckersBoard::kBlack) {
               EXPECT_TRUE(cell->mask & board.mBlack);
               EXPECT_EQ(cell->piece->kingRow, 7);
               EXPECT_EQ(cell->piece->backRow, 0);
            } else {
               EXPECT_TRUE(cell->mask & board.mWhite);
               EXPECT_EQ(cell->piece->kingRow, 0);
               EXPECT_EQ(cell->piece->backRow, 7);
            }
         } else {
            EXPECT_FALSE(cell->mask & (board.mWhite | board.mBlack));
         }
      }
   }

   EXPECT_EQ(board.mNumBlackRegular, 8);
   EXPECT_EQ(board.mNumBlackBackRow, 4);
   EXPECT_EQ(board.mNumBlackKing, 0);

   EXPECT_EQ(board.mNumWhiteRegular, 8);
   EXPECT_EQ(board.mNumWhiteBackRow, 4);
   EXPECT_EQ(board.mNumWhiteKing, 0);

   EXPECT_EQ(board.mRemovedPieces.size(), 0U);
   EXPECT_EQ(board.mMoveHist.size(), 0U);
}

TEST(CheckersBoardTest, MovePiece) {
   CheckersBoard board;

   // Move from back row to regular.
   board.MovePiece(board.mCells[0][0], board.mCells[3][0]);
   EXPECT_EQ(board.mNumBlackBackRow, 3);
   EXPECT_FALSE(board.mBlack & board.mCells[0][0]->mask);
   EXPECT_TRUE(board.mBlack & board.mCells[3][0]->mask);

   // Move it to a king.
   board.MovePiece(board.mCells[3][0], board.mCells[7][0]);
   EXPECT_EQ(board.mNumBlackKing, 1);

   // Move back to the back row.
   board.MovePiece(board.mCells[7][0], board.mCells[0][0]);
   EXPECT_EQ(board.mNumBlackKing, 1);
   EXPECT_EQ(board.mNumBlackBackRow, 4);

   // And back to a king spot.
   board.MovePiece(board.mCells[0][0], board.mCells[7][2]);
   EXPECT_EQ(board.mNumBlackKing, 1);
}

TEST(CheckersBoardTest, SingleCapture) {
   CheckersBoard board;

   board.MovePiece(board.mCells[5][1], board.mCells[3][1]);

   CheckersMove::LocVector locs;
   locs.push_back(std::make_pair(2, 0));
   locs.push_back(std::make_pair(3, 1));
   locs.push_back(std::make_pair(4, 2));

   board.ApplyMove(new CheckersMove(locs));

   EXPECT_EQ(board.mNumWhiteRegular, 7);
}

TEST(CheckersBoardTest, DoubleCapture) {
   CheckersBoard board;

   board.MovePiece(board.mCells[6][0], board.mCells[3][1]);

   CheckersMove::LocVector locs;
   locs.push_back(std::make_pair(2, 0));
   locs.push_back(std::make_pair(3, 1));
   locs.push_back(std::make_pair(4, 2));
   locs.push_back(std::make_pair(5, 1));
   locs.push_back(std::make_pair(6, 0));
   CheckersMove move(locs);

   board.ApplyMove(new CheckersMove(locs));

   EXPECT_EQ(board.mNumWhiteRegular, 6);
}

// Test AddCaptures for a simple single-piece capture.
TEST(CheckersBoardTest, AddCaptures) {
   CheckersBoard board;
   std::list<Board::Move *> moves;

   board.MovePiece(board.mCells[5][1], board.mCells[3][1]);

   board.AddCaptures(board.mCells[2][0], &moves);
   EXPECT_EQ(1U, moves.size());

   board.AddCaptures(board.mCells[2][2], &moves);
   EXPECT_EQ(2U, moves.size());
}

// Test AddCaptures for a multi-piece capture.
TEST(CheckersBoardTest, AddCaptures2) {
   CheckersBoard board;
   std::list<Board::Move *> moves;

   board.MovePiece(board.mCells[6][0], board.mCells[3][1]);

   board.AddCaptures(board.mCells[2][0], &moves);
   EXPECT_EQ(1U, moves.size());

   board.AddCaptures(board.mCells[2][2], &moves);
   EXPECT_EQ(2U, moves.size());
}

// Test GetAllMoves for the initial board.
TEST(CheckersBoardTest, GetAllMoves) {
   CheckersBoard board;

   std::list<Board::Move *> moves;
   board.GetAllMoves(&moves);

   EXPECT_EQ(7U, moves.size());
}

TEST(CheckersBoardTest, GetAllMovesForcedCapture) {
   CheckersBoard board;
   std::list<Board::Move *> moves;

   board.MovePiece(board.mCells[5][1], board.mCells[3][1]);
   board.GetAllMoves(&moves);

   EXPECT_EQ(2U, moves.size());
}

TEST(CheckersBoardTest, GameEnd) {
   CheckersBoard board;
   std::list<Board::Move *> moves;

   board.mBlack = 0;
   board.GetAllMoves(&moves);

   EXPECT_EQ(0U, moves.size());
   EXPECT_EQ(-CheckersBoard::kWinVal, board.GetValue());
}

TEST(CheckersBoardTest, UndoLastMove) {
   CheckersBoard board;

   board.ApplyMove(new CheckersMove(board.mCells[2][0], board.mCells[3][1]));
   board.UndoLastMove();
   EXPECT_EQ(0U, board.mMoveHist.size());
   EXPECT_TRUE(board.mCells[2][0]->piece);
   EXPECT_FALSE(board.mCells[3][1]->piece);

   board.MovePiece(board.mCells[5][1], board.mCells[3][1]);

   std::vector<const CheckersBoard::Cell *> locs;
   locs.push_back(board.mCells[2][0]);
   locs.push_back(board.mCells[3][1]);
   locs.push_back(board.mCells[4][2]);
   board.ApplyMove(new CheckersMove(locs));
   EXPECT_EQ(1U, board.mMoveHist.size());
   EXPECT_FALSE(board.mCells[2][0]->piece);
   EXPECT_FALSE(board.mCells[3][1]->piece);
   EXPECT_TRUE(board.mCells[4][2]->piece);

   board.UndoLastMove();
   EXPECT_EQ(0U, board.mMoveHist.size());
   EXPECT_TRUE(board.mCells[2][0]->piece);
   EXPECT_TRUE(board.mCells[3][1]->piece);
   EXPECT_FALSE(board.mCells[4][2]->piece);
}
*/

TEST(CheckersBoardTest, GetKey) {
   // Test equal boards.
   CheckersBoard board1, board2;
   const Board::Key *key1 = board1.GetKey();
   const Board::Key *key2 = board2.GetKey();
   EXPECT_TRUE(*key1 < *key2);
   delete key1; delete key2;
}

/*

   // Test that white's move > black's move.
   CheckersBoard board3, board4;
   //board3.mWhoseMove = CheckersBoard::kWhite;
   key1 = board3.GetKey(); key2 = board4.GetKey();
   if (!(*key2 < *key1))
      EXPECT_TRUE(false);
   delete key1; delete key2;

   // Test that regular black > no piece.
   CheckersBoard board5, board6;
   board5.MovePiece(board5.mCells[2][0], board5.mCells[3][0]);
   key1 = board5.GetKey(); key2 = board6.GetKey();
   if (!(*key2 < *key1))
      EXPECT_TRUE(false);
   delete key1; delete key2;

   // Test that regular white > regular black.
   CheckersBoard board7, board8;
   board8.RemovePiece(board8.mCells[5][1]);
   board8.MovePiece(board8.mCells[0][0], board8.mCells[5][1]);
   key1 = board7.GetKey(); key2 = board8.GetKey();
   if (!(*key2 < *key1))
      EXPECT_TRUE(false);
   delete key1; delete key2;

   // Test that black king > regular white.
   CheckersBoard board9, board10;
   board9.RemovePiece(board9.mCells[7][1]);
   board9.MovePiece(board9.mCells[0][0], board9.mCells[7][1]);
   key1 = board9.GetKey(); key2 = board10.GetKey();
   if (!(*key2 < *key1))
      EXPECT_TRUE(false);
   delete key1; delete key2;

   // Test that white king > black king.
   CheckersBoard board11, board12;
   board11.mCells[7][1]->piece->rank = CheckersBoard::kKing;
   board12.RemovePiece(board12.mCells[7][1]);
   board12.MovePiece(board12.mCells[0][0], board12.mCells[7][1]);
   key1 = board11.GetKey(); key2 = board12.GetKey();
   if (!(*key2 < *key1))
      EXPECT_TRUE(false);
   delete key1; delete key2;
}
*/

/*
TEST(CheckersBoardTest, TestPlay1) {
   CheckersBoard board;
   board.ApplyMove(new CheckersMove(board.mCells[2][2], board.mCells[3][1]));
   board.ApplyMove(new CheckersMove(board.mCells[5][1], board.mCells[4][2]));
   board.ApplyMove(new CheckersMove(board.mCells[1][3], board.mCells[2][2]));

   std::list<Board::Move *> moves;
   board.GetAllMoves(&moves);
   EXPECT_EQ(7U, moves.size());
}

TEST(CheckersBoardTest, TestPlay2) {
   CheckersBoard board;
   board.ApplyMove(new CheckersMove(board.mCells[2][2], board.mCells[3][1]));
   board.ApplyMove(new CheckersMove(board.mCells[5][1], board.mCells[4][2]));
   board.ApplyMove(new CheckersMove(board.mCells[1][3], board.mCells[2][2]));
   board.ApplyMove(new CheckersMove(board.mCells[5][3], board.mCells[4][4]));

   std::list<Board::Move *> moves;
   board.GetAllMoves(&moves);
   EXPECT_EQ(1U, moves.size());
}
*/
