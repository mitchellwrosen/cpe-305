#include "Board.h"
#include "MyLib.h"
#include "PylosBoard.h"
#include "PylosMove.h"
#include "PylosView.h"

namespace {
   const char kWhitePiece = 'W';
   const char kBlackPiece = 'B';
   const char kNoPiece = '.';
}

// static
Class PylosView::mClass = Class("PylosView", &PylosView::Create);

const char PylosView::GetPiece(ulong mask) const
{
   return mask & mModel->GetWhite() ? kWhitePiece :
          mask & mModel->GetBlack() ? kBlackPiece :
          kNoPiece;
}

void PylosView::Draw(std::ostream &out) {
   int ndx;
   char c;
   ulong mask = 0x20000000;
   std::list<Board::Move *> allMoves;

   c = GetPiece(mask);
   out << "   " << c << std::endl << std::endl;

   mask = 0x2000000;
   for (int i = 0; i < 4; i++, mask = mask << 1) {
      c = GetPiece(mask);
      if (i % 2 == 0)
         out << "  " << c;
      else
         out << " " << c << std::endl << std::endl;
   }

   mask = 0x10000;
   for (int i = 0; i < 9; i++, mask = mask << 1) {
      c = GetPiece(mask);
      out << " " << c;
      if (i % 3 == 2)
         out << std::endl << std::endl;
   }

   mask = 0x1;
   for (int i = 0; i < 16; i++, mask = mask << 1) {
      c = GetPiece(mask);
      if (i % 4 != 0)
         out << " ";
      out << c;
      if (i % 4 == 3)
         out << std::endl << std::endl;
   }

   if (mModel->GetWhoseMove())
      out << "Black's move" << std::endl << std::endl;
   else
      out << "White's move" << std::endl << std::endl;
}

const Class* PylosView::GetClass() const {
   return Class::ForName("PylosView");
}

// static
Object *PylosView::Create() {
   return new PylosView();
}
