#ifndef BASICKEY_H_
#define BASICKEY_H_

#include "Board.h"
#include "Class.h"
#include "MyLib.h"

template<int n>
class BasicKey : public Board::Key {
public:
   // Object implementation.
   const Class* GetClass() const
   {
      return &mClass;
   }

   void *operator new(size_t sz)
   {
      void *temp;

      if (mFreeList.size()) {
         temp = mFreeList.back();
         mFreeList.pop_back();
      } else {
         temp = ::new char[sz];
      }

      mOutstanding++;
      return temp;
   }

   void operator delete(void *p)
   {
      mFreeList.push_back((BasicKey<n> *) p);
      mOutstanding--;
   }

   // Board:Key implementation.
   bool operator==(const Board::Key& rhs) const
   {
      const BasicKey<n>& other = dynamic_cast<const BasicKey<n>& >(rhs);
      for (int i = 0; i < n; i++) {
         if (vals[i] != other.vals[i])
            return false;
      }
      return true;
   }

   bool operator<(const Board::Key& rhs) const
   {
      const BasicKey<n>& other = dynamic_cast<const BasicKey<n>& >(rhs);
      for (int i = 0; i < n; i++) {
         if (vals[i] != other.vals[i])
            return vals[i] < other.vals[i];
      }
      return false;
   }

   std::istream& Read(std::istream &is)
   {
      return is;
   }

   std::ostream& Write(std::ostream &os) const
   {
      return os;
   }

   static Object *Create();
   static Class mClass;
   static std::vector<BasicKey<n> *> mFreeList;

   ulong vals[n];
};

// static
template<int n>
std::vector<BasicKey<n> *> BasicKey<n>::mFreeList;

// static
template<int n>
Object *BasicKey<n>::Create()
{
   // Zero-out the key.
   BasicKey<n> *key = new BasicKey<n>();
   for (int i = 0; i < n; i++)
      key->vals[i] = 0;
   return key;
}

// static
template<int n>
Class BasicKey<n>::mClass = Class(FString("BasicKey<%d>", n),
 &BasicKey<n>::Create);

#endif   // BASICKEY_H_
