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

void PrintUsageAndExit()
{
   std::cout << "Give me the right class you silly goose" << std::endl;
   exit(1);
}

void ClearMovesList(std::list<Board::Move *>* moves)
{
   for (std::list<Board::Move *>::iterator iter = moves->begin();
        iter != moves->end(); iter++) {
      delete *iter;
   }

   moves->clear();
}

void PrintMoves(const std::list<const Board::Move *> &moves)
{
   int longestMoveLen = 0;
   int curLineLen = 0;

   if (moves.empty())
      return;

   for (std::list<const Board::Move *>::const_iterator iter = moves.begin();
         iter != moves.end(); iter++) {
      int moveLen = ((std::string) **iter).length();
      if (moveLen > longestMoveLen)
         longestMoveLen = moveLen;
   }

   for (std::list<const Board::Move *>::const_iterator iter = moves.begin();
         iter != moves.end(); iter++) {
      std::string moveString = (std::string) **iter;
      if (curLineLen + longestMoveLen >= 80) {
         std::cout << std::endl;
         curLineLen = 0;
      }

      if (curLineLen != 0)
         std::cout << " ";
      std::cout << std::setw(longestMoveLen) << std::left <<
       moveString;
      curLineLen += longestMoveLen + 1;
   }

   std::cout << std::endl;
}

int main(int argc, char **argv)
{
   Board *board = 0, *cmpBoard;
   View *view;
   Dialog *dlg;
   Board::Move *move, *cmpMove;
   const Board::Key *key, *cmpKey;
   void *options;
   std::list<Board::Move *> moves;
   std::list<const Board::Move *> constMoves;

   unsigned int count;
   std::string command, cArg;
   long seed;

   // Sample of some Class code
   const Class *viewCls, *dlgCls;
   const BoardClass *brdCls;

   if (argc < 2)
      PrintUsageAndExit();

   brdCls = dynamic_cast<const BoardClass *>(Class::ForName(argv[1]));
   viewCls = brdCls->GetViewClass();
   dlgCls = brdCls->GetDlgClass();

   board = dynamic_cast<Board *>(brdCls->NewInstance());
   view = dynamic_cast<View *>(viewCls->NewInstance());
   dlg = dynamic_cast<Dialog *>(dlgCls->NewInstance());
   view->SetModel(board);

   move = board->CreateMove();

   while (std::cin >> command) {
      try {
         if (command.compare("showBoard") == 0) {
            view->Draw(std::cout);
            board->GetAllMoves(&moves);

            std::cout << "All Moves: " << std::endl;
            PrintMoves(*reinterpret_cast<std::list<
             const Board::Move *> *>(&moves));

            ClearMovesList(&moves);
         } else if (command.compare("enterMove") == 0) {
            getline(std::cin, cArg);
            *move = cArg.c_str();
         } else if (command.compare("showMove") == 0) {
            std::cout << (std::string) *move << std::endl;
         } else if (command.compare("applyMove") == 0) {
            board->ApplyMove(move->Clone());
         } else if (command.compare("doMove") == 0) {
            getline(std::cin, cArg);
            *move = cArg.c_str();
            board->ApplyMove(move->Clone());
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

            std::cout << std::endl << "Move History: " << std::endl;
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
            std::ifstream in(cArg.c_str(), std::ifstream::in |
             std::ifstream::out | std::ifstream::binary);
            in >> *board;
         } else if (command.compare("loadMove") == 0) {
            std::cin >> cArg;
            std::ifstream in(cArg.c_str());
            in >> *move;
         } else if (command.compare("compareKeys") == 0) {
            std::cin >> cArg;
            std::ifstream in(cArg.c_str());
            cmpBoard = dynamic_cast<Board *>(brdCls->NewInstance());
            in >> *cmpBoard;

            key = board->GetKey();
            cmpKey = cmpBoard->GetKey();
            if (*key == *cmpKey) {
               std::cout << "Board keys are equal" << std::endl;
            } else {
               std::cout << "Board keys are unequal" << std::endl <<
                "Current board is ";

               if (*key < *cmpKey)
                  std::cout << "less ";
               else
                  std::cout << "greater ";

               std::cout << "than " << cArg.c_str() << std::endl;
            }

            delete key;
            delete cmpKey;
            delete cmpBoard;
         } else if (command.compare("compareMove") == 0) {
            getline(std::cin, cArg);
            cmpMove = board->CreateMove();
            *cmpMove = cArg.c_str();

            if (*move == *cmpMove) {
               std::cout << "Moves are equal" << std::endl;
            } else if (*move < *cmpMove) {
               std::cout << "Current move is less than entered move" <<
                std::endl;
            } else {
               std::cout << "Current move is greater than entered move" <<
                std::endl;
            }

            delete cmpMove;
         } else if (command.compare("setOptions") == 0) {
            options = brdCls->GetOptions();

            if (dlg->Run(std::cin, std::cout, options))
               brdCls->SetOptions(options);

            free(options);
         } else if (command.compare("testPlay") == 0) {
            std::cin >> seed;
            std::cin >> count;
            srand(seed);

            for (unsigned int i = 0; i < count; i++) {
               board->GetAllMoves(&moves);
               if (!moves.empty()) {
                  std::list<Board::Move *>::iterator iter = moves.begin();
                  for (int j = 0, n = rand() % moves.size(); j < n; j++, iter++)
                     ;
                  board->ApplyMove((*iter)->Clone());
                  ClearMovesList(&moves);
               }
            }
         } else if (command.compare("testRun") == 0) {
            std::cin >> seed;
            std::cin >> count;
            srand(seed);

            for (unsigned int i = 0; i < count; i++) {
               board->GetAllMoves(&moves);
               if (!moves.empty()) {
                  std::list<Board::Move *>::iterator iter = moves.begin();
                  for (int j = 0, n = rand() % moves.size(); j < n; j++, iter++)
                     ;
                  board->ApplyMove((*iter)->Clone());
                  ClearMovesList(&moves);
               } else {
                  for (int i = 0, n = rand() % board->GetMoveHist().size();
                   i <= n; i++) {
                     board->UndoLastMove();
                  }
               }
            }
         } else if (command.compare("keyMoveCount") == 0) {
            std::cout << "Moves/Keys: " << Board::Move::GetOutstanding() << "/"
             << Board::Key::GetOutstanding() << std::endl;
         } else if (command.compare("quit") == 0) {
            break;
         } else if (std::cin.eof()) {
            std::cin.clear();
            throw BaseException("Unexpected EOF");
         } else {
            std::cout << "Unknown command: " << command << std::endl;
         }
      } catch (BaseException e) {
         std::cout << "Error: " << e.what() << std::endl;
      }

      std::cout << std::endl;
   }

   delete board;

   return 0;
}
