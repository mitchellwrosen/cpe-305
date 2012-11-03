#include "Board.h"
#include "PylosMove.h"
#include "PylosView.h"

// static
Class PylosView::mClass = Class("PylosView", &PylosView::Create);

// static
Class *PylosView::GetClassPtr() { return &mClass; }

// static
Object *PylosView::Create() { return new PylosView(); }

void PylosView::SetModel(const Board *brd)
 { mModel = dynamic_cast<const PylosBoard *>(brd); }

void PylosView::Draw(std::ostream &out)
{
   ulong mask;
   const PylosBoard *model = dynamic_cast<const PylosBoard *>(mModel);

   for (int level = PylosBoard::kDim - 1; level >= 0; level--) {
      mask = PylosBoard::kCellMasks[level];
      for (int i = 0; i < PylosBoard::kDim - level; i++) {
         for (int j = 0; j < level; j++)
            out << " ";
         for (int j = 0; j < PylosBoard::kDim - level; j++, mask <<= 1)
            out << model->GetPieceChar(mask) << " ";
         out << std::endl << std::endl;
      }
   }

   if (mModel->GetWhoseMove())
      out << "Black's move" << std::endl;
   else
      out << "White's move" << std::endl;
}
