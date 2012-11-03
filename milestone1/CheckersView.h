#ifndef PYLOSVIEW_H_
#define PYLOSVIEW_H_

#include "Class.h"
#include "View.h"

class CheckersView : public View {
public:
   // View implementation.
   virtual void Draw(std::ostream &out);
   virtual void SetModel(const Board *brd);

   // Object implementation.
   virtual const Class *GetClass() const;

   static Class *GetClassPtr();

protected:
   static Class mClass;
};

#endif   // PYLOSVIEW_H_
