#ifndef PYLOSVIEW_H_
#define PYLOSVIEW_H_

#include <iostream>
#include "Class.h"
#include "CheckersBoard.h"
#include "View.h"

class CheckersView : public View {
public:
   // View implementation.
   virtual void Draw(std::ostream &out);
   virtual void SetModel(const Board *brd)
   {
      mModel = dynamic_cast<const CheckersBoard *>(brd);
   }

   char GetPiece(ulong mask) const;

   // Object implementation.
   virtual const Class *GetClass() const
   {
      return Class::ForName("CheckersView");
   }

   static Class *GetClassPtr();

   static Object *Create();

protected:
   static Class mClass;
   const CheckersBoard *mModel;
};

#endif   // PYLOSVIEW_H_
