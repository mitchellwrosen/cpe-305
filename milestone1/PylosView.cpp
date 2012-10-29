#include "Board.h"
#include "MyLib.h"
#include "PylosMove.h"
#include "PylosView.h"

namespace {
   const char kWhitePiece = 'W';
   const char kBlackPiece = 'B';
   const char kNoPiece = '.';

   ulong kLevelThreeMask = 0x20000000;
   ulong kLevelTwoMask = 0x2000000;
   ulong kLevelOneMask = 0x10000;
   ulong kLevelZeroMask = 0x1;

   const int kNumLevelThreeCells = 1;
   const int kNumLevelTwoCells = 4;
   const int kNumLevelOneCells = 9;
   const int kNumLevelZeroCells = 16;
}

// static
Class PylosView::mClass = Class("PylosView", &PylosView::Create);

// static
Class *PylosView::GetClassPtr()
{
   return &mClass;
}

// static
Object *PylosView::Create()
{
   return new PylosView();
}


char PylosView::GetPiece(ulong mask) const
{
   const PylosBoard *pb = dynamic_cast<const PylosBoard *>(mModel);
   return mask & pb->GetWhite() ? kWhitePiece :
    mask & pb->GetBlack() ? kBlackPiece : kNoPiece;
}

void PylosView::Draw(std::ostream &out)
{
   char c;
   ulong mask = kLevelThreeMask;
   std::list<Board::Move *> allMoves;

   c = GetPiece(mask);
   out << "   " << c << " " << std::endl << std::endl;

   mask = kLevelTwoMask;
   for (int i = 0; i < kNumLevelTwoCells; i++, mask <<= 1) {
      c = GetPiece(mask);
      if (i % 2 == 0)
         out << "  ";
      out << c << " ";
      if (i % 2 == 1)
         out << std::endl << std::endl;
   }

   mask = kLevelOneMask;
   for (int i = 0; i < kNumLevelOneCells; i++, mask = mask << 1) {
      c = GetPiece(mask);
      if (i % (PylosBoard::kDim - 1) == 0)
         out << " ";
      out << c << " ";
      if (i % (PylosBoard::kDim - 1) == 2)
         out << std::endl << std::endl;
   }

   mask = kLevelZeroMask;
   for (int i = 0; i < kNumLevelZeroCells; i++, mask = mask << 1) {
      c = GetPiece(mask);
      out << c << " ";
      if (i % PylosBoard::kDim == PylosBoard::kDim - 1)
         out << std::endl << std::endl;
   }

   if (mModel->GetWhoseMove())
      out << "Black's move" << std::endl;
   else
      out << "White's move" << std::endl;
}
