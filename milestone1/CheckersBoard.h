#ifndef CHECKERSBOARD_H
#define CHEKERSBOARD_H

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

      Rules() : kingWgt(300), backRowWgt(100), moveWgt(20) {}

      int GetKingWgt()  {return kingWgt;}
      int GetBackRowWgt() {return backRowWgt;}
      int GetMoveWgt()   {return moveWgt;}

      void SetKingWgt(int val);
      void SetBackRowWgt(int val);
      void SetMoveWgt(int val);

      void EndSwap();
   };

   CheckersBoard();

   // Board implementation.
   virtual ~CheckersBoard() {/* TODO? */}
   virtual long GetValue() const;
   virtual void ApplyMove(Move *);
   virtual void UndoLastMove();
   virtual void GetAllMoves(std::list<Move *> *) const;
   virtual Move *CreateMove() const;
   virtual int GetWhoseMove() const {return mWhoseMove != kWhite;}

   virtual const std::list<const Move *> &GetMoveHist() const
    {return *(std::list<const Move *> *)&mMoveHist;}

   virtual Board *Clone() const;
   virtual const Key *GetKey() const;

   const Class *GetClass() const;
   static Object *Create();

   const uint64_t GetWhite() const {return mWhite;}
   const uint64_t GetWhiteKing() const {return mWhiteKing;}
   const uint64_t GetBlack() const {return mBlack;}
   const uint64_t GetBlackKing() const {return mBlackKing;}

   // Option accessor/mutator.  GetOptions returns dynamically allocated
   // object representing options. SetOptions takes similar object.  Caller
   // owns object in both cases.
   static void *GetOptions();
   static void SetOptions(const void *opts);

protected:
   enum Piece {kNone, kWhite, kWhiteKing, kBlack, kBlackKing}
   struct Cell {
      int row;
      int col;
      Piece piece;

      Cell(int row, int col) : row(row), col(col), piece(kNone) { }
   };
   const static int kNumCells = 64;
   static Cell mCells[kNumCells];

   std::istream &Read(std::istream &);
   std::ostream &Write(std::ostream &) const;

   inline void HalfPut(Cell *cell) const {
      //spt->top = spt->empty;
      //spt->empty = spt->top->above;

      //if (mWhoseMove == kWhite)
         //mWhite |= spt->top->mask;
      //else
         //mBlack |= spt->top->mask;
   }

   inline void HalfTake(Cell *cell) const {
      //spt->empty = spt->top;
      //if (spt->empty->level != 0)
         //spt->top = spt->empty->below[kNW];
      //else
         //spt->top = NULL;

      //if (mWhoseMove == kWhite)
         //mWhite &= ~spt->empty->mask;
      //else
         //mBlack &= ~spt->empty->mask;
   }

   // HalfPut the first loc and HalfTake the rest.
   void HalfApplyMove(CheckersMove *move) const;

   // HalfPut the second and onward locs, HalfTake the first.
   void UnHalfApplyMove(CheckersMove *move) const;

   static BoardClass mClass;

   // Rules object for CheckersBoard
   static Rules mRules;

   // Bitmasks indicating which cells contain a white/black piece/king.
   // Row-major order. Piece masks include pieces AND kings.
   uint64_t mWhite;
   uint64_t mWhiteKing;
   uint64_t mBlack;
   uint64_t mBlackKing;

   int mWhoseMove;    // Whose move currently
   int mWhiteReserve; // How many marbles has white in his reserve
   int mBlackReserve; // How many marbles has black in his reserve
   int mLevelLead;    // Amount by which white leads in terms of marble level
   int mFreeLead;     // Amount of promoteable marbles white has over black.

   // History of moves leading to this point.
   std::list<Move *> mMoveHist;
};

#endif
