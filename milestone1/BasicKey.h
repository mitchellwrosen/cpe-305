#ifndef BASICKEY_H_
#define BASICKEY_H_

#include "Board.h"
#include "Class.h"
#include "MyLib.h"

template<int n>
class BasicKey : public Board::Key {
public:
   // Object implementation.
   const Class* GetClass() const {
      return &mClass;
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

   std::istream& Read(std::istream &is) {
      // TODO
      return is;
   }

   std::ostream& Write(std::ostream &os) const {
      // TODO
      return os;
   }

   static Object *Create();
   static Class mClass;

   ulong vals[n];
};

// static
template<int n>
Object *BasicKey<n>::Create()
{
   return new BasicKey<n>();
}
// static
template<int n>
Class BasicKey<n>::mClass = Class(FString("BasicKey<%d>", n),
 &BasicKey<n>::Create);

#endif   // BASICKEY_H_
