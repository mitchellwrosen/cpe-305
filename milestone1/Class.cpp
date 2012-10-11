#include "Class.h"
#include "OthelloBoard.h"

#include <string>

// Dummy
namespace {
   Object *Dummy() {
   }
}

// Class //////////////////////////////////////////////////////////////////////

// static
Class::Class(const std::string &n, Object *(*c)())
{
   // TODO
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

Object *Class::NewInstance() const 
{
   // TODO: more?
   //return mCreate();
   return NULL;
}



// BoardClass /////////////////////////////////////////////////////////////////
BoardClass::BoardClass(const std::string& n, Object *(*c)(),
 const std::string &fn, bool useXPos, int minPlayers)
 : Class(n, c)
{
   // TODO
}

void *BoardClass::GetOptions() const 
{
   // TODO
   return NULL;
}

void BoardClass::SetOptions(void *opts) const
{
   // TODO
}

/*
// OthelloBoardClass //////////////////////////////////////////////////////////
OthelloBoardClass::OthelloBoardClass(const std::string &n, Object *(*c)(),
 const std::string &fn, bool useXPos, int minPlayers)
 : BoardClass(n, c, fn, useXPos, minPlayers) 
{
   // TODO
}

void *OthelloBoardClass::GetOptions() const 
{
   // TODO
}

void OthelloBoardClass::SetOptions(void *opts) const
{
   // TODO
}
*/
