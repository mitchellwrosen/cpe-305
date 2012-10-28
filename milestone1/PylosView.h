#ifndef PYLOSVIEW_H_
#define PYLOSVIEW_H_

#include <iostream>
#include "Class.h"
#include "PylosBoard.h"
#include "View.h"

class PylosView : public View {
public:
   // View implementation.
   virtual void Draw(std::ostream &out);
   virtual void SetModel(const Board *brd)
   {
      mModel = dynamic_cast<const PylosBoard *>(brd);
   }

   char GetPiece(ulong mask) const;

   // Object implementation.
   virtual const Class *GetClass() const { return Class::ForName("PylosView"); }

   static Class *GetClassPtr();
   static Object *Create();

protected:
   static Class mClass;
};

#endif   // PYLOSVIEW_H_
