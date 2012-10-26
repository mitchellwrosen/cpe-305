#ifndef CHECKERSDLG_H
#define CHECKERSDLG_H

#include <iostream>

#include "Class.h"
#include "Dialog.h"
#include "CheckersBoard.h"

class CheckersDlg : public Dialog {
public:
   bool Run(std::istream &in, std::ostream &out, void *data);

   static Object* Create();

   // Object implementation.
   const Class *GetClass() const { return Class::ForName("CheckersDlg"); }

   static Class *GetClassPtr();

protected:
   static Class mClass;

private:
   void ReadMethodInt(std::istream &in, std::ostream &out, std::string,
    CheckersBoard::Rules *, void (CheckersBoard::Rules::*x)(int));
};

#endif   // CHECKERSDLG_H
