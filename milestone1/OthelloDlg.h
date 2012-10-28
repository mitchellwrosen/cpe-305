#ifndef OTHELLODLG_H
#define OTHELLODLG_H

#include "Dialog.h"

class OthelloDlg : public Dialog {
public:
   bool Run(std::istream &in, std::ostream &out, void *data);

   static Object *Create();

   const Class *GetClass() const { return Class::ForName("OthelloDlg"); }

   static Class *GetClassPtr();

protected:
   static Class mClass;
};

#endif
