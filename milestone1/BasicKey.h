#ifndef BASICKEY_H_
#define BASICKEY_H_

#include "Board.h"
#include "Class.h"

template<int n>
class BasicKey : public Board::Key {
public:
   // Object implementation.
   const Class* GetClass() const {
      // TODO
   }

   // Board:Key implementation.
   bool operator==(const Board::Key&) const {
      // TODO
   }

   bool operator<(const Board::Key&) const {
      // TODO
   }

   std::istream& Read(std::istream&) {
      // TODO
   }

   std::ostream& Write(std::ostream&) const {
      // TODO
   }

   ulong* vals;
};

#endif   // BASICKEY_H_
