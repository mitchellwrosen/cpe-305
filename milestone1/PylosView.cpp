#include "Board.h"
#include "MyLib.h"
#include "PylosBoard.h"
#include "PylosMove.h"
#include "PylosView.h"

namespace {
   const char kWhitePiece = 'W';
   const char kBlackPiece = 'B';
   const char kNoPiece = '.';

   // Mirrors enum in PylosBoard
   int kWhite = 1;
   int kBlack = -1;
}

void PylosView::Draw(std::ostream &out) {
   int ndx;
   char c;
   ulong mask;
   std::list<Board::Move *> allMoves;

   for (ndx = 0, mask = 0x20000000; mask; ndx++, mask >> 1) {
      c = mask & mModel->GetWhite() ? kWhitePiece :
          mask & mModel->GetBlack() ? kBlackPiece :
          kNoPiece;
      if (ndx < 1) {
         out << "   " << c << "\n" << std::endl;
      } else if (ndx < 5) {
         if (((ndx - 1) % 2) == 0)
            out << "  " << c;
         else
            out << " " << c << "\n" << std::endl;
      } else if (ndx < 14) {
         out << " " << c;
         if (((ndx - 5) % 3) == 2)
            out << "\n" << std::endl;
      } else {
         if (((ndx - 14) % 4) != 0)
            out << " ";
         out << c;
         if (((ndx - 14) % 4) == 3)
            out << "\n" << std::endl;
      }
   }

   if (mModel->GetWhoseMove() == kWhite)
      out << "White's move\n" << std::endl;
   else
      out << "Black's move\n" << std::endl;

   out << "All Moves:" << std::endl;

   mModel->GetAllMoves(&allMoves);
   for (std::list<Board::Move *>::const_iterator iter = allMoves.begin();
        iter != allMoves.end(); iter++) {
      // TODO: Newlines every once in a while. Meh.
      PylosMove *pm = dynamic_cast<PylosMove *>(*iter);
      out << (std::string)(*pm) << " ";
   }
   out << std::endl;
}

const Class* PylosView::GetClass() const {
   const Class* cls = Class::ForName("PylosView");

   if (cls)
      return cls;

   return new Class("PylosView", &PylosView::Create);
}

// static
Object *Create() {
   return new PylosView();
}
