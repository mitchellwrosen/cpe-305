#include "Board.h"
#include "MyLib.h"
#include "CheckersMove.h"
#include "CheckersView.h"

namespace {
   const char kWhitePiece = 'w';
   const char kBlackPiece = 'b';
   const char kNoPiece = '.';
}

// static
Class CheckersView::mClass = Class("CheckersView", &CheckersView::Create);

// static
Class *CheckersView::GetClassPtr()
{
   return &mClass;
}

// static
Object *Create()
{
   return new CheckersView();
}

char CheckersView::GetPiece(ulong mask) const
{
   return mask & mModel->GetWhite() ? kWhitePiece :
          mask & mModel->GetBlack() ? kBlackPiece :
          kNoPiece;
}

void CheckersView::Draw(std::ostream &out) {
}
