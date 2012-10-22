#include <assert.h>
#include "Class.h"

// Class //////////////////////////////////////////////////////////////////////

Class::Class(const std::string &n, Object *(*c)()) : mName(n), mCreate(c)
{
   Class *clsPtr = mClsHead;
   if (mClsHead == NULL) {
      mClsHead = this;
   } else {
      while (clsPtr->mNext) {
         assert(mName != clsPtr->GetName());
         clsPtr = clsPtr->mNext;
      }

      clsPtr->mNext = this;
   }
}

Object *Class::NewInstance() const {
   return mCreate();
}

// static
const Class *Class::ForName(const std::string &name)
{
   Class *clsPtr = mClsHead;
   while (clsPtr && clsPtr->mName != name)
      clsPtr = clsPtr->mNext;

   return clsPtr;
}

// static
Class *Class::mClsHead;  // Pointer to general list of Classes

// BoardClass /////////////////////////////////////////////////////////////////

BoardClass::BoardClass(const std::string& n, Object *(*c)(),
 const std::string &fn, const std::string &vn, const std::string &dn,
 void *(*getOptions)(), void (*setOptions)(const void *), bool useXPos,
 int minPlayers)
 : Class(n, c), mFriendlyName(fn), mGetOptions(getOptions),
   mSetOptions(setOptions), mUseXPos(useXPos), mMinPlayers(minPlayers)
{
   mViewClass = Class::ForName(vn);
   mDlgClass = Class::ForName(dn);

   BoardClass *brdClsPtr = mBrdClsHead;
   if (mBrdClsHead == NULL) {
      mBrdClsHead = this;
   } else {
      while (brdClsPtr->mNext)
         brdClsPtr = brdClsPtr->mNext;

      brdClsPtr->mNext = this;
   }
}

void *BoardClass::GetOptions() const {
   return (*mGetOptions)();
}

void BoardClass::SetOptions(const void *opts) const {
   (*mSetOptions)(opts);
}

// static
std::vector<const BoardClass *> BoardClass::GetAllClasses()
{
   std::vector<const BoardClass *> brdClasses;
   BoardClass *brdClsPtr = mBrdClsHead;

   while (brdClsPtr) {
      brdClasses.push_back(brdClsPtr);
      brdClsPtr = brdClsPtr->mNext;
   }

   return brdClasses;
}

// static
BoardClass *BoardClass::mBrdClsHead;
