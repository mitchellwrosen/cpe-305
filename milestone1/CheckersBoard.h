#ifndef CHECKERSBOARD_H
#define CHEKERSBOARD_H

#include <stdint.h>
#include <assert.h>
#include <iostream>
#include <set>
#include <vector>
#include <string.h>
#include "Class.h"
#include "MyLib.h"
#include "Board.h"

class CheckersMove;

class CheckersBoard : public Board {
public:
   const static int kDim = 8;

   friend class CheckersMove;

   struct Rules {
      int kingWgt;
      int backRowWgt;
      int moveWgt;
      const int pieceWgt;

      Rules() : kingWgt(300), backRowWgt(100), moveWgt(20), pieceWgt(100) { }

      int GetKingWgt() const { return kingWgt; }
      int GetBackRowWgt() const { return backRowWgt; }
      int GetMoveWgt() const { return moveWgt; }
      int GetPieceWgt() const { return pieceWgt; }

      void SetKingWgt(int val);
      void SetBackRowWgt(int val);
      void SetMoveWgt(int val);

      void EndSwap();
   };

   CheckersBoard();

   // Board implementation.
   virtual ~CheckersBoard() { Delete(); }
   virtual long GetValue() const;
   virtual void ApplyMove(Move *);
   virtual void UndoLastMove();
   virtual void GetAllMoves(std::list<Move *> *) const;
   virtual Move *CreateMove() const;
   virtual int GetWhoseMove() const {return mWhoseMove;}

   virtual const std::list<const Move *> &GetMoveHist() const
    {return *(std::list<const Move *> *)&mMoveHist;}

   virtual Board *Clone() const;
   virtual const Key *GetKey() const;

   const Class *GetClass() const;
   static Object *Create();

   uint64_t GetWhite() const {return mWhite;}
   uint64_t GetBlack() const {return mBlack;}

   // Option accessor/mutator.  GetOptions returns dynamically allocated
   // object representing options. SetOptions takes similar object.  Caller
   // owns object in both cases.
   static void *GetOptions();
   static void SetOptions(const void *opts);

   static void StaticInit();

protected:
   enum { kWhite = -1, kBlack = 1 };
   struct Cell {
      int row;
      int col;
      uint64_t mask;

      Cell(int row, int col, uint64_t mask) : row(row), col(col), mask(mask) { }
   };
   static Cell mCells[kDim][kDim];

   class Piece {
   public:
      enum Rank { kNormal, kKing };

      Piece(Cell *cell, int whose);

      const Cell *GetCell() const { return mCell; }
      Rank GetRank() const { return mRank; }

      int GetWhose() const { return mWhose; }
      int GetKingRow() const { return mKingRow; }
      int GetBackRow() const { return mBackRow; }

      // Sets the cell and adjusts the piece's rank accordingly. Returns if the
      // piece was promoted from a normal piece to a king.
      void SetCell(Cell* cell) {
         mCell = cell;
         if (IsOnKingRow() && mRank != kKing)
            mRank = kKing;
      }
      void SetRank(Rank rank) { mRank = rank; }

      bool IsOnKingRow() { return mCell->row == mKingRow; }
      bool IsOnBackRow() { return mCell->row == mBackRow; }

   private:
      Cell *mCell;
      Rank mRank;

      const int mWhose;
      const int mKingRow;
      const int mBackRow;
   };

   class StaticInitializer {
   public:
      StaticInitializer() { CheckersBoard::StaticInit(); }
   };
   static StaticInitializer staticInitializer;

   inline bool PieceAt(Cell* cell) {
      uint64_t mask = 1 << (cell->row * kDim + cell->col);
      return mask & (mBlack|mWhite);
   }

   std::istream &Read(std::istream &);
   std::ostream &Write(std::ostream &) const;

   // Adjust the board bitmasks and |piece| to reflect |piece| being moved to
   // |cell|. Promote the piece to a king if necessary.
   // Return if the piece was promoted or not.
   inline void HalfMove(Cell *cell, Piece *piece) {
      uint64_t& mask = piece->GetWhose() == kBlack ? mBlack : mWhite;
      mask &= ~piece->GetCell()->mask;
      mask |= cell->mask;
      piece->SetCell(cell);
   }

   void MovePiece(Cell *target, Piece *piece);

   // HalfPut the first loc and HalfTake the rest.
   void HalfApplyMove(CheckersMove *move) const;

   // HalfPut the second and onward locs, HalfTake the first.
   void UnHalfApplyMove(CheckersMove *move) const;

   void Delete();

   static BoardClass mClass;

   // Rules object for CheckersBoard
   static Rules mRules;

   // Bitmasks indicating which cells contain a white/black piece.
   // Row-major order.
   uint64_t mWhite;
   uint64_t mBlack;

   // Rolling counts for computing GetValue() simply and without loops. These
   // variables offer no more information than can be found in the above masks.
   int mNumWhite;          // Total number of white pieces.
   int mNumWhiteBackRow;   // Number of white pieces on the back row.
   int mNumWhiteKing;      // Number of white kings.

   int mNumBlack;
   int mNumBlackBackRow;
   int mNumBlackKing;

   // Piece arrays.
   std::set<Piece> mWhitePieces;
   std::set<Piece> mBlackPieces;

   int mWhoseMove;    // Whose move it is (kWhiteMove or kBlackMove)

   // History of moves leading to this point.
   std::list<Move *> mMoveHist;
};

#endif
