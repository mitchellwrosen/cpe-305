#ifndef CHECKERSBOARD_H
#define CHECKERSBOARD_H

#include <stdint.h>
#include <list>
#include <string.h>
#include "Class.h"
#include "MyLib.h"
#include "Board.h"

typedef std::pair<int8_t, int8_t> Location;
typedef std::vector<Location> LocVector;

class CheckersMove;

class CheckersBoard : public Board {
public:
   const static int kDim = 8;
   const static int kBitsPerLong = 32;
   const static int kDirs[];

   friend class CheckersMove;
   enum { kBlack = 1, kWhite = -1 };
   enum { kRegular, kKing };

   struct Rules {
      int kingWgt, backRowWgt, moveWgt;
      const int pieceWgt;
      Rules() : kingWgt(300), backRowWgt(100), moveWgt(20), pieceWgt(100) { }
      void EndSwap();
   };

   struct Piece {
      Location loc;
      int rank;
      const int whose, kingRow, backRow;
      Piece(int row, int col, const int whose) : loc(std::make_pair(row, col)),
       rank(kRegular), whose(whose), kingRow(whose == kBlack ? kDim - 1 : 0),
       backRow(whose == kBlack ? 0 : kDim - 1) { }
   };

   struct Cell {
      const Location loc;
      uint64_t mask;
      Piece *piece;
      Cell(int row, int col, uint64_t mask) : loc(std::make_pair(row, col)),
       mask(mask), piece(NULL) { }
   };

   CheckersBoard();

   // Board implementation.
   virtual ~CheckersBoard() { Delete(); }
   virtual long GetValue() const;
   virtual void ApplyMove(Move *);
   virtual void UndoLastMove();
   virtual void GetAllMoves(std::list<Move *> *) const;
   virtual Move *CreateMove() const;
   virtual int GetWhoseMove() const { return mWhoseMove; }

   virtual const std::list<const Move *> &GetMoveHist() const
    {return *(std::list<const Move *> *)&mMoveHist;}

   virtual Board *Clone() const;
   virtual const Key *GetKey() const;

   const Class *GetClass() const;
   static Object *Create();

   static void *GetOptions();
   static void SetOptions(const void *opts);

   uint64_t GetBlack() { return mBlack; }
   uint64_t GetWhite() { return mWhite; }
   const Cell *GetCell(int row, int col) const { return mCells[row][col]; }

#ifndef GTEST_INCLUDE_GTEST_GTEST_H_
protected:
#endif
   std::istream &Read(std::istream &);
   std::ostream &Write(std::ostream &) const;

   void AddPiece(Cell *cell);
   void RemovePiece(Cell *cell);
   // Returns if the piece was promoted or not.
   bool MovePiece(Location &src, Location &dst);

   inline Piece *PieceAt(int row, int col) const;
   inline Cell *CellAt(Location &loc) const;
   inline Cell *CellFrom(Location &loc, int dr, int dc) const;
   inline bool IsCellEmpty(const Cell *cell) const;
   inline Cell *CellInbetween(Location cell1,
    Location cell2) const;

   // Helper to GetAllMoves.
   void AddCaptures(Piece *piece, std::list<Move *> *moves) const;

   void Init();
   void Delete();

   static BoardClass mClass;

   // Rules object for CheckersBoard
   static Rules mRules;

   int mWhoseMove;    // Whose move it is (kBlack or kWhite).

   mutable uint64_t mBlack, mWhite;

   Cell *mCells[kDim][kDim];
   std::list<Piece *> mPieces;
   std::list<Piece *> mRemovedPieces;
   std::list<Move *> mMoveHist;
};

#endif   // CHECKERSBOARD_H
