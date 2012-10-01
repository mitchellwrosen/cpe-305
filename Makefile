# General test makefile for multi-target test
# Copyright Clinton Staley 12/1/01


# General definitions
CPP = g++
CPPFLAGS = -w

CHESSOBJS = ChessBoard.o ChessMove.o ChessView.o ChessDlg.o  
OTHELLOOBJS = OthelloBoard.o OthelloMove.o OthelloView.o OthelloDlg.o
MANCALAOBJS = MancalaBoard.o MancalaMove.o MancalaView.o MancalaDlg.o
CHECKERSOBJS = CheckersBoard.o CheckersMove.o CheckersView.o CheckersDlg.o
GAMEOBJS = Board.o Dialog.o Class.o $(CHESSOBJS) $(OTHELLOOBJS) $(MANCALAOBJS) $(CHECKERSOBJS)
           
BOARDTESTOBJS = BoardTest.o $(GAMEOBJS)
MYBOARDTESTOBJS = MyBoardTest.o $(GAMEOBJS)
MAKEBOOKOBJS = MakeBook.o GameModel.o Book.o $(GAMEOBJS)
MINIMAXAPPOBJS = MinimaxApp.o GameView.o GameModel.o Book.o $(GAMEOBJS)

# Object file generation rules
all: MinimaxApp

MyBoardTest : $(MYBOARDTESTOBJS)
	$(CPP) $(MYBOARDTESTOBJS) -o MyBoardTest

BoardTest : $(BOARDTESTOBJS)
	$(CPP) $(BOARDTESTOBJS) -o BoardTest

MakeBook : $(MAKEBOOKOBJS)
	$(CPP) $(MAKEBOOKOBJS) -o MakeBook

MinimaxApp : $(MINIMAXAPPOBJS)
	$(CPP) $(MINIMAXAPPOBJS) -o MinimaxApp

clean:
	rm BoardTest ChessBoardTest MakeBook MinimaxApp *.o


# Header file interdependencies
GameModel.h: Board.h
	touch GameModel.h

Board.h: Class.h
	touch Board.h

OthelloBoard.h OthelloMove.h ChessBoard.h ChessMove.h: Board.h
	touch OthelloBoard.h OthelloMove.h ChessBoard.h ChessMove.h

OthelloView.h ChessView.h: View.h
	touch OthelloView.h ChessView.h

OthelloDlg.h ChessDlg.h: Dialog.h
	touch OthelloDlg.h ChessDlg.h


# Object file generation rules
Class.o: Class.h
	$(CPP) $(CPPFLAGS) -c Class.cpp

Board.o: Board.h Board.cpp
	$(CPP) $(CPPFLAGS) -c Board.cpp

BoardTest.o: BoardTest.cpp
	$(CPP) $(CPPFLAGS) -c BoardTest.cpp

MyBoardTest.o: MyBoardTest.cpp
	$(CPP) $(CPPFLAGS) -c MyBoardTest.cpp

Dialog.o: Dialog.h Class.h
	$(CPP) $(CPPFLAGS) -c Dialog.cpp

OthelloBoard.o: OthelloBoard.cpp OthelloMove.h OthelloBoard.h MyLib.h Class.h
	$(CPP) $(CPPFLAGS) -c OthelloBoard.cpp

OthelloMove.o: OthelloMove.cpp OthelloMove.h OthelloBoard.h MyLib.h Class.h
	$(CPP) $(CPPFLAGS) -c OthelloMove.cpp

OthelloView.o: OthelloView.h OthelloBoard.h View.h MyLib.h Class.h
	$(CPP) $(CPPFLAGS) -c OthelloView.cpp

OthelloDlg.o: OthelloDlg.cpp OthelloDlg.h OthelloBoard.h Dialog.h MyLib.h Class.h
	$(CPP) $(CPPFLAGS) -c OthelloDlg.cpp

ChessBoard.o: ChessBoard.cpp ChessBoard.h MyLib.h Class.h
	$(CPP) $(CPPFLAGS) -c ChessBoard.cpp

ChessMove.o: ChessMove.cpp ChessBoard.h ChessMove.h
	$(CPP) $(CPPFLAGS) -c ChessMove.cpp

ChessView.o: ChessView.h ChessBoard.cpp ChessBoard.h View.h MyLib.h Class.h Class.cpp
	$(CPP) $(CPPFLAGS) -c ChessView.cpp

ChessDlg.o: ChessDlg.h ChessBoard.cpp ChessBoard.h Dialog.h Dialog.cpp MyLib.h Class.h Class.cpp
	$(CPP) $(CPPFLAGS) -c ChessDlg.cpp

MakeBook.o: MakeBook.cpp MyLib.h GameModel.h 
	$(CPP) $(CPPFLAGS) -c $<

GameModel.o: GameModel.cpp GameModel.h Board.h Class.h
	$(CPP) $(CPPFLAGS) -c GameModel.cpp

GameView.o: GameView.cpp GameView.h Board.h Class.h
	$(CPP) $(CPPFLAGS) -c GameView.cpp

Book.o: Book.cpp Book.h
	$(CPP) $(CPPFLAGS) -c Book.cpp

.cpp.o: 
	$(CPP) $(CPPFLAGS) -c $<

