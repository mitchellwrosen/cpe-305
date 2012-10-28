#include "OthelloView.h"
#include "OthelloBoard.h"

using namespace std;

// static
Class OthelloView::mClass = Class("OthelloView", &OthelloView::Create);

// static
Class *OthelloView::GetClassPtr()
{
   return &mClass;
}

// static
Object *OthelloView::Create()
{
   return new OthelloView();
}

void OthelloView::Draw(ostream &out)
{
   string rtn;
   int row, col;
   char sqr;
   const OthelloBoard *ob = dynamic_cast<const OthelloBoard *>(mModel);

   for (row = 0; row < OthelloBoard::dim; row++) {
      for (col = 0; col < OthelloBoard::dim; col++) {
         sqr = ob->GetSquare(row, col);
         rtn += sqr == OthelloBoard::mWPiece ? "W"
          : sqr == OthelloBoard::mBPiece ? "B" : ".";
      }
      rtn += "\n";
   }
   rtn += ob->GetWhoseMove() ? "W\n" : "B\n";

   out << rtn;
}
