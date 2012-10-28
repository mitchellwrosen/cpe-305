#ifndef CHECKERSMOVE_H
#define CHECKERSMOVE_H

#include <iostream>
#include <list>
#include <vector>
#include "CheckersBoard.h"

class CheckersMove : public Board::Move {
public:
   enum { kMove, kCapture };

   friend class CheckersBoard;

   CheckersMove() : mToKing(false) { }
   CheckersMove(const LocVector &locs) : mLocs(locs), mToKing(false) { }
   CheckersMove(const Location &src, const Location &dst);
   virtual ~CheckersMove() { }

   // Board::Move implementation.
   virtual bool operator==(const Board::Move &rhs) const;
   virtual bool operator<(const Board::Move &rhs) const;
   virtual operator std::string() const;
   virtual void operator=(const std::string &src);
   virtual Board::Move *Clone() const;

   inline bool IsCapture()
   {
      return TAbs<int8_t>(mLocs[0].first - mLocs[1].first) == 2;
   }

   void *operator new(size_t sz);
   void operator delete(void *p);

#ifndef GTEST_INCLUDE_GTEST_GTEST_H_
protected:
#endif
   std::istream &Read(std::istream &is);
   std::ostream &Write(std::ostream &) const;

   LocVector mLocs;
   bool mToKing;

   static std::vector<CheckersMove *> mFreeList;
};

#endif   // CHECKERSMOVE_H
