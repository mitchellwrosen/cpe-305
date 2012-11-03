#include "Board.h"
#include "CheckersMove.h"
#include "CheckersView.h"

static Object *Create() { return new CheckersView(); }

// static
Class CheckersView::mClass = Class("CheckersView", &Create);

// static
Class *CheckersView::GetClassPtr() { return &mClass; }

void CheckersView::SetModel(const Board *brd)
 { mModel = dynamic_cast<const CheckersBoard *>(brd); }

const Class *CheckersView::GetClass() const 
 { return Class::ForName("CheckersView"); }

void CheckersView::Draw(std::ostream &out)
{
   const CheckersBoard *model = dynamic_cast<const CheckersBoard *>(mModel);

   out << "           White" << std::endl << std::endl;
   for (int row = CheckersBoard::kDim - 1; row >= 0; row--) {
      out << (char) ('A' + row) << "  ";
      for (int col = 0; col < CheckersBoard::kDim; col++)
         out << model->GetPieceChar(row, col) << "  ";
      out << std::endl;
   }
   out << "   1  2  3  4  5  6  7  8" << std::endl << std::endl;
   out << "           Black" << std::endl << std::endl;

   if (mModel->GetWhoseMove() == CheckersBoard::kBlack)
      out << "Black's move" << std::endl;
   else
      out << "White's move" << std::endl;
}
