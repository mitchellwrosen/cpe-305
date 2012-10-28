#include "MyLib.h"
#include "CheckersDlg.h"

// static
Class CheckersDlg::mClass = Class("CheckersDlg", &CheckersDlg::Create);

// static
Class *CheckersDlg::GetClassPtr()
{
   return &mClass;
}

// static
Object *CheckersDlg::Create()
{
   return new CheckersDlg();
}

bool CheckersDlg::Run(std::istream &in, std::ostream &out, void *data)
{
   char resp;

   CheckersBoard::Rules *rules = (CheckersBoard::Rules *) data;
   out << "(Piece weight is always 100)" << std::endl;
   out << "King weight: " << rules->kingWgt << std::endl;
   out << "Back row weight: " << rules->backRowWgt << std::endl;
   out << "Move weight: " << rules->moveWgt << std::endl << std::endl;
   out << "Modify? [y/n] ";

   if ((in >> resp).eof())
      throw BaseException("Unexpected EOF");

   while (in.get() != '\n' && !in.eof())
      ;

   if (resp == 'y') {
      out << std::endl;
      Dialog::ReadLimitInt(in, out, &rules->kingWgt, 0, 1001,
       "Enter king weight [0, 1000]: ");
      Dialog::ReadLimitInt(in, out, &rules->backRowWgt, 0, 1001,
       "Enter back-row weight [0, 1000]: ");
      Dialog::ReadLimitInt(in, out, &rules->moveWgt, 0, 101,
       "Enter move weight [0, 100]: ");
   }

   return resp == 'y';
}
