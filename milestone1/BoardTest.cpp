#include <stdlib.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <list>
#include "MyLib.h"
#include "Board.h"
#include "View.h"
#include "Dialog.h"
// Add more includes, possibly, but not board-specific ones
#include "PylosBoard.h" // TODO remove
#include "PylosView.h" // TODO remove

void PrintUsageAndExit() {
   std::cout << "Usage: TODO" << std::endl;
   exit(1);
}

int main(int argc, char **argv)
{
   Board *board = 0, *cmpBoard;
   Board::Move *move, *cmpMove;
   int argLen, count;
   std::string command, cArg;
   // Many more locals needed

   // Sample of some Class code
   const Class *viewCls, *dlgCls;
   const BoardClass *brdCls;

   if (argc > 2)
      PrintUsageAndExit();

   // TODO stuff

   // Set up Class objects based on commandline args, with appropriate
   // error handling, so that this works...
   // board = dynamic_cast<Board *>(brdCls->NewInstance());

   // Just a sampling of the main scaffold-loop.  You'll make yours a lot longer,
   // will need to use a try/catch block, and are welcome to violate the function
   // line limit rule for this one method.
   PylosBoard *pb = new PylosBoard();
   //View *pv = dynamic_cast<View *>(dynamic_cast<BoardClass *>(
   // const_cast<Class *>(pb->GetClass()))->GetViewClass()->NewInstance());
   PylosView *pv = new PylosView();
   pv->SetModel(pb);

   while (std::cin >> command) {
      if (command.compare("undoLastMove") == 0) {
         std::cin >> count;

         if (count > board->GetMoveHist().size())
            count = board->GetMoveHist().size();

         while (count-- > 0)
            board->UndoLastMove();
      } else if (command.compare("enterMove") == 0) {
         getline(std::cin, cArg);
         *move = cArg.c_str();
      } else if (command.compare("saveBoard") == 0) {
         std::cin >> cArg;
         std::ofstream out(cArg.c_str());
         out << *board;
      } else if (command.compare("showVal") == 0) {
         std::cout << "Value: " << board->GetValue() << std::endl;
      } else if (command.compare("showBoard") == 0) {
         pv->Draw(std::cout);
      } else if (command.compare("quit") == 0) {
         break;
      } else {
         std::cout << "Unknown command: " << command << std::endl;
      }

      std::cout << std::endl;
   }

   delete board;

   return 0;
}
