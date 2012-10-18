#include <assert.h>
#include "Class.h"
#include "OthelloBoard.h"

#include <string>

// Class //////////////////////////////////////////////////////////////////////

Class::Class(const std::string &n, Object *(*c)()) : mName(n), mCreate(c)
{
   Class *clsPtr = mClsHead;
   if (mClsHead) {
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
Class *Class::mClsHead = NULL;  // Pointer to general list of Classes

// BoardClass /////////////////////////////////////////////////////////////////

BoardClass::BoardClass(const std::string& n, Object *(*c)(),
 const std::string &fn, void *(*getOptions)(), void (*setOptions)(const void *),
 bool useXPos, int minPlayers)
 : Class(n, c), mFriendlyName(fn), mGetOptions(getOptions),
   mSetOptions(setOptions), mUseXPos(useXPos), mMinPlayers(minPlayers)
{
   mViewClass = Class::ForName(mFriendlyName.append("View"));
   mDlgClass = Class::ForName(mFriendlyName.append("Dlg"));

   BoardClass *brdClsPtr = mBrdClsHead;
   if (mBrdClsHead) {
      mBrdClsHead = this;
   } else {
      while (brdClsPtr->mNext)
         brdClsPtr = brdClsPtr->mNext;

      brdClsPtr->mNext = this;
   }
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
BoardClass *BoardClass::mBrdClsHead = NULL;

