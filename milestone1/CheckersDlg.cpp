#include "CheckersDlg.h"
#include "CheckersBoard.h"

static Object *Create() { return new CheckersDlg(); }

// static
Class CheckersDlg::mClass = Class("CheckersDlg", &Create);

// static
Class *CheckersDlg::GetClassPtr() { return &mClass; }

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
      Dialog::ReadLimitInt(in, out, &rules->kingWgt, 0, 1000,
       "Enter king weight");
      Dialog::ReadLimitInt(in, out, &rules->backRowWgt, 0, 1000,
       "Enter back-row weight");
      Dialog::ReadLimitInt(in, out, &rules->moveWgt, 0, 100,
       "Enter move weight");
   }

   return resp == 'y';
}
