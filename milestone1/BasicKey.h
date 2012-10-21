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
   bool operator==(const Board::Key& rhs) const {
      const BasicKey<n>& other = dynamic_cast<const BasicKey<n>& >(rhs);
      for (int i = 0; i < n; i++) {
         if (vals[i] != other.vals[i])
            return false;
      }
      return true;
   }

   bool operator<(const Board::Key& rhs) const {
      const BasicKey<n>& other = dynamic_cast<const BasicKey<n>& >(rhs);
      for (int i = 0; i < n; i++) {
         if (vals[i] < other.vals[i])
            return true;
      }
      return false;
   }

   std::istream& Read(std::istream&) {
      // TODO
   }

   std::ostream& Write(std::ostream&) const {
      // TODO
   }

   // TODO: static class objects?

   ulong vals[n];
};

#endif   // BASICKEY_H_
