#ifndef CHECKERSDLG_H
#define CHECKERSDLG_H

#include <iostream>

#include "Class.h"
#include "Dialog.h"

class CheckersDlg : public Dialog {
public:
   bool Run(std::istream &in, std::ostream &out, void *data);

   // Object implementation.
   const Class *GetClass() const { return &mClass; }
   static Class *GetClassPtr();

private:
   static Class mClass;
};

#endif   // CHECKERSDLG_H
