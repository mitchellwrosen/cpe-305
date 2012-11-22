#ifndef MYHEAP_H
#define MYHEAP_H
// Use of MYHEAP prevents conflict with HEAP_H declared in STL heap.h file
#include <assert.h>
#include <limits.h>
#include "MyLib.h"

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
   Heap(const Heap<Base> &src)      {Copy(src);}
   virtual ~Heap(void)              {Delete();}
   const Heap<Base> &operator=(const Heap<Base> &src)
    {if (this != &src) {Delete(); Copy(src);} return *this;};

   long Count(void) const {return end;}
   long Limit(void) const {return limit;}

   virtual long Add(const Base &);
   virtual long Remove(Base *pVal);
   virtual void Adjust(long id, const Base &val);

   void Check(void) const;

protected:
   /* Some member data to fill in, here */
   long limit;
   long end;

   /* Recommended useful private methods. */
   long Promote(const Base &val, long ndx);
   long Demote(const Base &val, long ndx);
   void Copy(const Heap<Base> &src);
   void Delete(void);
   void Resize(long incr);
};


#endif
