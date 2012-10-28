#ifndef OTHELLOVIEW_H
#define OTHELLOVIEW_H

#include "View.h"
#include "OthelloBoard.h"

class OthelloView : public View {
public:
   virtual void Draw(std::ostream &out);
   virtual void SetModel(const Board *brd)
   {
      mModel = dynamic_cast<const OthelloBoard *>(brd);
   }

   // Object impl.
   virtual const Class *GetClass() const 
   {
      return Class::ForName("OthelloBoard");
   }

   static Class *GetClassPtr();
   static Object *Create();

protected:
   static Class mClass;
};

#endif
