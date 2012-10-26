#include "Board.h"
#include "MyLib.h"
#include "CheckersMove.h"
#include "CheckersView.h"

namespace {
   const char kBlackPiece = 'b';
   const char kBlackKind = 'B';
   const char kWhitePiece = 'w';
   const char kWhiteKing = 'W';
   }
char PieceChar(const CheckersBoard::Piece *piece)
{
   if (piece == NULL)
      return '.';

   if (piece->whose == CheckersBoard::kBlack) {
      if (piece->rank == CheckersBoard::kRegular)
         return 'b';
      else
         return 'B';
   } else {
      if (piece->rank == CheckersBoard::kRegular)
         return 'w';
      else
         return 'W';
   }

}

// static
Class CheckersView::mClass = Class("CheckersView", &CheckersView::Create);

// static
Class *CheckersView::GetClassPtr()
{
   return &mClass;
}

// static
Object *CheckersView::Create()
{
   return new CheckersView();
}

void CheckersView::Draw(std::ostream &out)
{
   out << "           White" << std::endl << std::endl;
   for (int row = CheckersBoard::kDim - 1; row >= 0; row--) {
      for (int col = 0; col < CheckersBoard::kDim; col++) {
         if (col == 0)
            out << (char) ('A' + row) << "  ";
         out << PieceChar(mModel->GetCell(row, col)->piece) << "  ";
         if (col == CheckersBoard::kDim - 1)
            out << std::endl;
      }
   }
   out << "   1  2  3  4  5  6  7  8" << std::endl << std::endl;
   out << "           Black" << std::endl << std::endl;
   if (mModel->GetWhoseMove() == CheckersBoard::kBlack)
      out << "Black's move" << std::endl << std::endl;
   else
      out << "White's move" << std::endl << std::endl;
}
