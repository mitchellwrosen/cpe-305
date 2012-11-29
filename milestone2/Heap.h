#ifndef MYHEAP_H
#define MYHEAP_H
// Use of MYHEAP prevents conflict with HEAP_H declared in STL heap.h file
#include <assert.h>
#include <limits.h>
#include <string.h>
#include <list>
#include "MyLib.h"

#include <iostream> //TODO remove

// Heap implements a max heap of Base objects (largest object is on the top).
// It uses the array-based tree representation typical of data structures
// like the heap, where it's possible to keep the tree complete at all
// times.  Heap assumes that its instantiating type "Base" has an operator<,
// and can be assigned and default constructed.  No other assumptions are
// made about Base.
//
// Items on the heap are indentified by unique integer id values.  Though an
// item moves about in the heap as other items are added and deleted, its id
// value remains the same for as long as it is on the heap.  This system allows
// the heap user to identify an item in the middle of the heap, for adjustment
// or removal, without needing to know details of the heap operation, or keep
// track of the movement of items within the heap.
//
// The Heap constructor takes an initial size for the heap.  This initial
// size is not a limit on the heap size, however.  If an Add call has no
// space to add to the heap, the Add call automatically increases the
// size of the heap by an amount equal to the size originally given in the
// constructor.  (Thus the initial size is also a "size increment".)
//
// Type members:
// HEntry -- An "item" on the heap, including the value and the id.
//
// Data members:
// limit  -- the maximum number of items in the heap.
// incr   -- amount to increment the heap size by when necessary.
// end    -- the index of the next empty element in the heap array.
// data   -- the pointer to the block of HEntry elements comprising the heap.
// map    -- pointer to a block of "limit" ints, which map from an id to the
//           current location of that item in the "data" array.
// free   -- Unused id's are tracked via a freelist within the "map" array.
//           Each unused entry contains the index of the next unused entry,
//           negated (thus -5 indicates the next free entry is index 5),
//           ending with a map entry set to LONG_MIN.
//
// Public Methods, with order of complexity listed for each:
// Heap   -- Initialize heap with size "lm" and no data                O(n)
// Count  -- returns the current number of items in the heap.          O(1)
// Limit  -- returns the max number of items in the heap.              O(1)
// Add    -- Adds a new Base to the heap.  Returns an identifying handle or
//           "id" for that item, to use with "Adjust" if necessary.    O(log n)
// Remove -- Places into *pVal the maximum item on the heap, and removes that
//           item from the heap.  Returns the id of the removed item.  O(log n)
// Adjust -- Adjusts the item with id "id" to have the new value "val". Promotes
//           or demotes the item within the heap if necessary.  The item retains
//           the same id value after this operation, however.          O(log n)

template <class Base>
struct Heap {
   Heap(long lm);
   Heap(const Heap<Base> &src) { Copy(src); }
   virtual ~Heap()             { Delete(); }
   const Heap<Base> &operator=(const Heap<Base> &src)
    {if (this != &src) {Delete(); Copy(src);} return *this;};

   long Count() const {return end;}
   long Limit() const {return limit;}

   virtual long Add(const Base &val);
   virtual long Remove(Base *pVal);
   virtual void Adjust(long id, const Base &val);

   void Check() const;

#ifndef GTEST_INCLUDE_GTEST_GTEST_H_
protected:
#endif
   struct HEntry {
      HEntry() { };
      HEntry(const Base &val, int id) : val(val), id(id) { };
      ~HEntry() { };

      Base val;
      int id;
   };

   long incr;     // amount to increment the heap size by when necessary
   long cap;      // the maximum heap size before a Resize() is required
   long limit;
   long end;

   HEntry *data;
   long *map;
   long free;      // (negative) index of map representing the first free index

   void Promote(long ndx);
   void Demote(long ndx);
   void Swap(int ndx1, int ndx2);
   void Copy(const Heap<Base> &src);
   void Delete();
   void Resize();
};

template <class Base>
Heap<Base>::Heap(long lm) : incr(lm), cap(lm), limit(999), end(0),
 free(LONG_MIN)
{
   data = new HEntry[incr];
   map = new long[incr];
   for (int i = 0; i < incr; i++)
      map[i] = limit;
}

template <class Base>
long Heap<Base>::Add(const Base &val)
{
   //std::cout << "Adding " << val << std::endl;

   int id;

   if (end == cap)
      Resize();

   if (free == LONG_MIN) {
      id = end;
   } else {
      id = -free;
      free = map[-free];
   }

   data[end] = HEntry(val, id);
   map[id] = end;
   Promote(end);

   end++;

   return id;
}

template <class Base>
long Heap<Base>::Remove(Base *pVal) {
   if (end == 0)
      return -1;

   //std::cout << "Removing " << data[0].val << std::endl;
   assert(map[data[0].id] == 0);

   long thisFree, nextFree, retId;

   // Set up return vals.
   *pVal = data[0].val;
   retId = data[0].id;

   // The old map index containing 0 is now free. Insert it into the freelist.
   // Special case: no free list yet, or this id is < -free.
   if (free == LONG_MIN || data[0].id < -free) {
      map[data[0].id] = free;
      free = -data[0].id;
   } else {
      thisFree = free;
      nextFree = map[-thisFree];
      while (nextFree > -data[0].id) {
         thisFree = nextFree;
         nextFree = map[-thisFree];
      }
      map[-thisFree] = -data[0].id;
      map[data[0].id] = nextFree;
   }

   end--;

   if (end != 0) {
      data[0] = data[end];
      map[data[0].id] = 0;

      Demote(0);
   }

   return retId;
}

template <class Base>
void Heap<Base>::Adjust(long id, const Base &val)
{
   // TODO
   //data[map[id]].val = val;
   //Promote(data[map[id]], map[id]);
   //Demote(data[map[id]], map[id]);
}

// Premotes Base |val| at index |ndx| to its proper location at the heap.
// Adjusts data and map accordingly.
template <class Base>
void Heap<Base>::Promote(long ndx)
{
   long parentNdx = (ndx-1)/2;

   while (ndx != 0 && data[parentNdx].val < data[ndx].val) {
      Swap(ndx, parentNdx);

      ndx = parentNdx;
      parentNdx = (ndx-1)/2;
   }
}

template <class Base>
void Heap<Base>::Swap(int ndx1, int ndx2)
{
   HEntry tempEntry;
   long tempId;

   // Swap data entries.
   tempEntry = data[ndx1];
   data[ndx1] = data[ndx2];
   data[ndx2] = tempEntry;

   // Swap map entries.
   tempId = map[data[ndx1].id];
   map[data[ndx1].id] = map[data[ndx2].id];
   map[data[ndx2].id] = tempId;
}

template <class Base>
void Heap<Base>::Demote(long ndx)
{
   int child1Ndx = 2*ndx + 1;
   int child2Ndx = 2*ndx + 2;
   int maxChildNdx;

   while (true) {
      // This node may have no children.
      if (child1Ndx >= end)
         break;

      maxChildNdx = child1Ndx;
      if (child2Ndx < end && data[child1Ndx].val < data[child2Ndx].val)
         maxChildNdx = child2Ndx;

      // If this entry is bigger than both of its children, we're done demoting.
      if (!(data[ndx].val < data[maxChildNdx].val))
         break;

      Swap(ndx, maxChildNdx);

      ndx = maxChildNdx;
      child1Ndx = 2*ndx + 1;
      child2Ndx = 2*ndx + 2;
   }
}

template <class Base>
void Heap<Base>::Delete()
{
   // TODO
}

template <class Base>
void Heap<Base>::Resize()
{
   HEntry *newData = new HEntry[cap + incr];
   memcpy(newData, data, cap * sizeof(HEntry));

   long *newMap = new long[cap + incr];
   memcpy(newMap, map, cap * sizeof(long));

   delete[] map;
   map = newMap;

   delete[] data;
   data = newData;

   cap += incr;
}

#endif
