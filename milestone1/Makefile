# General test makefile for multi-target test
# Copyright Clinton Staley 12/1/01


# General definitions
CPP = g++
CPPFLAGS = -w -g

OTHELLOOBJS = OthelloBoard.o OthelloMove.o OthelloView.o OthelloDlg.o
PYLOSOBJS = PylosBoard.o PylosMove.o PylosView.o PylosDlg.o
CHECKERSOBJS = CheckersBoard.o CheckersMove.o CheckersView.o CheckersDlg.o
GAMEOBJS = Board.o Dialog.o Class.o $(CHESSOBJS) $(OTHELLOOBJS) $(PYLOSOBJS) $(CHECKERSOBJS)

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
	rm BoardTest *.o


# Header file interdependencies
GameModel.h: Board.h
	touch GameModel.h

Board.h: Class.h
	touch Board.h

OthelloBoard.h OthelloMove.h: Board.h
	touch OthelloBoard.h OthelloMove.h

OthelloView.h: View.h
	touch OthelloView.h

OthelloDlg.h: Dialog.h
	touch OthelloDlg.h


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

PylosBoard.o: PylosBoard.cpp PylosMove.h PylosBoard.h MyLib.h Class.h
	$(CPP) $(CPPFLAGS) -c PylosBoard.cpp

PylosMove.o: PylosMove.cpp PylosMove.h PylosBoard.h MyLib.h Class.h
	$(CPP) $(CPPFLAGS) -c PylosMove.cpp

PylosView.o: PylosView.h PylosBoard.h View.h MyLib.h Class.h
	$(CPP) $(CPPFLAGS) -c PylosView.cpp

PylosDlg.o: PylosDlg.cpp PylosDlg.h PylosBoard.h Dialog.h MyLib.h Class.h
	$(CPP) $(CPPFLAGS) -c PylosDlg.cpp

.cpp.o:
	$(CPP) $(CPPFLAGS) -c $<
