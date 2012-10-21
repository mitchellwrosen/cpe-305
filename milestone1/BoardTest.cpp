#include <stdlib.h>
#include <assert.h>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include "MyLib.h"
#include "Board.h"
#include "View.h"
#include "Dialog.h"
// Add more includes, possibly, but not board-specific ones
#include "PylosBoard.h" // TODO remove
#include "PylosView.h" // TODO remove
#include "PylosMove.h"

void PrintUsageAndExit()
{
   std::cout << "Usage: TODO" << std::endl;
   exit(1);
}

bool CompareMoves(Board::Move *m1, Board::Move *m2)
{
   return *m1 < *m2;
}

void PrintMoves(const std::list<const Board::Move *> &moves)
{
   int longestMoveLen = 0;
   int curLineLen = 0;

   for (std::list<const Board::Move *>::const_iterator iter = moves.begin();
         iter != moves.end(); iter++) {
      int moveLen = ((std::string) **iter).length();
      if (moveLen > longestMoveLen)
         longestMoveLen = moveLen;
   }
   for (std::list<const Board::Move *>::const_iterator iter = moves.begin();
         iter != moves.end(); iter++) {
      std::string moveString = (std::string) **iter;
      if (curLineLen + longestMoveLen > 80) {
         std::cout << std::endl;
         curLineLen = 0;
      }
      std::cout << std::setw(longestMoveLen+1) << std::left <<
         moveString + " ";
      curLineLen += longestMoveLen + 1;
   }
}

int main(int argc, char **argv)
{
   Board *board = 0, *cmpBoard;
   View *view;
   Board::Move *move, *cmpMove;
   int argLen, count;
   std::string command, cArg;
   // Many more locals needed
   std::list<Board::Move *> moves;
   std::list<const Board::Move *> constMoves;

   // Sample of some Class code
   const Class *viewCls, *dlgCls;
   const BoardClass *brdCls;

   if (argc > 2)
      PrintUsageAndExit();

   brdCls = dynamic_cast<const BoardClass *>(Class::ForName(argv[1]));
   viewCls = brdCls->GetViewClass();
   dlgCls = brdCls->GetDlgClass();

   // Set up Class objects based on commandline args, with appropriate
   // error handling, so that this works...
   // board = dynamic_cast<Board *>(brdCls->NewInstance());

   // Just a sampling of the main scaffold-loop.  You'll make yours a lot longer,
   // will need to use a try/catch block, and are welcome to violate the function
   // line limit rule for this one method.
   board = new PylosBoard();
   cmpBoard = new PylosBoard();
   //View *pv = dynamic_cast<View *>(dynamic_cast<BoardClass *>(
   // const_cast<Class *>(pb->GetClass()))->GetViewClass()->NewInstance());
   view = new PylosView();
   view->SetModel(board);

   std::vector<std::pair<short, short> > locs(1);
   move = new PylosMove(locs, PylosMove::kReserve);

   while (std::cin >> command) {
      try {
         if (command.compare("showBoard") == 0) {
            view->Draw(std::cout);

            board->GetAllMoves(&moves);
            moves.sort(CompareMoves);
            std::cout << "All Moves:" << std::endl;
            PrintMoves(*reinterpret_cast<std::list<const Board::Move *> *>(&moves));
         } else if (command.compare("enterMove") == 0) {
            getline(std::cin, cArg);
            *move = cArg.c_str();
         } else if (command.compare("showMove") == 0) {
            std::cout << (std::string) *move << std::endl;
         } else if (command.compare("applyMove") == 0) {
            board->ApplyMove(move);
         } else if (command.compare("doMove") == 0) {
            getline(std::cin, cArg);
            *move = cArg.c_str();
            board->ApplyMove(move);
         } else if (command.compare("undoLastMove") == 0) {
            std::cin >> count;

            if (count > board->GetMoveHist().size())
               count = board->GetMoveHist().size();

            while (count-- > 0)
               board->UndoLastMove();
         } else if (command.compare("showVal") == 0) {
            std::cout << "Value: " << board->GetValue() << std::endl;
         } else if (command.compare("showMoveHist") == 0) {
            constMoves = board->GetMoveHist();
            std::cout << "Move History:" << std::endl;
            PrintMoves(constMoves);
         } else if (command.compare("saveBoard") == 0) {
            std::cin >> cArg;
            std::ofstream out(cArg.c_str());
            out << *board;
         } else if (command.compare("saveMove") == 0) {
            std::cin >> cArg;
            std::ofstream out(cArg.c_str());
            out << *move;
         } else if (command.compare("loadBoard") == 0) {
            std::cin >> cArg;
            std::ifstream in(cArg.c_str());
            in >> *board;
         } else if (command.compare("loadMove") == 0) {
            std::cin >> cArg;
            std::ifstream in(cArg.c_str());
            in >> *move;
         } else if (command.compare("compareKeys") == 0) {
            std::cin >> cArg;
            std::ifstream in(cArg.c_str());
            in >> *cmpBoard;
            if (*board->GetKey() == *cmpBoard->GetKey()) {
               std::cout << "Board keys are equal" << std::endl;
            } else {
               std::cout << "Board keys are unequal" << std::endl <<
                "Current board is ";
               if (*board->GetKey() < *cmpBoard->GetKey())
                  std::cout << "less ";
               else
                  std::cout << "greater ";
               std::cout << "than " << cArg.c_str() << std::endl;
            }
         } else if (command.compare("setOptions") == 0) {
            // TODO
         } else if (command.compare("quit") == 0) {
            break;
         } else {
            std::cout << "Unknown command: " << command << std::endl;
         }
         std::cout << std::endl;
      } catch (BaseException e) {
         std::cout << "Error: " << e.what() << std::endl;
      }
   }

   delete board;

   return 0;
}
