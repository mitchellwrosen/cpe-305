# General test makefile for multi-target test
# Copyright Clinton Staley 12/1/01


# General definitions
CPP = g++
PROFFLAGS =
CPPFLAGS = $(PROFFLAGS) -Wall -std=c++98 -g

OTHELLOOBJS = OthelloBoard.o OthelloMove.o OthelloView.o OthelloDlg.o
PYLOSOBJS = PylosBoard.o PylosMove.o PylosView.o PylosDlg.o
CHECKERSOBJS = CheckersBoard.o CheckersMove.o CheckersView.o CheckersDlg.o
GAMEOBJS = Board.o Dialog.o Class.o $(OTHELLOOBJS) $(PYLOSOBJS) $(CHECKERSOBJS)

BOARDTESTOBJS = BoardTest.o $(GAMEOBJS)

# Object file generation rules
all: BoardTest

BoardTest : $(BOARDTESTOBJS)
	$(CPP) $(PROFFLAGS) $(BOARDTESTOBJS) -o BoardTest

clean:
	rm BoardTest *.o
	cp MyBoardTest.o.backup MyBoardTest.o

# Object file generation rules
Class.o: Class.h
	$(CPP) $(CPPFLAGS) -c Class.cpp

Board.o: Board.h Board.cpp
	$(CPP) $(CPPFLAGS) -c Board.cpp

BoardTest.o: BoardTest.cpp
	$(CPP) $(CPPFLAGS) -c BoardTest.cpp

Dialog.o: Dialog.h Class.h
	$(CPP) $(CPPFLAGS) -c Dialog.cpp

OthelloBoard.o: OthelloBoard.cpp OthelloMove.h OthelloBoard.h MyLib.h Class.h
	$(CPP) $(CPPFLAGS) -c OthelloBoard.cpp

OthelloMove.o: OthelloMove.cpp OthelloMove.h OthelloBoard.h MyLib.h Class.h
	$(CPP) $(CPPFLAGS) -c OthelloMove.cpp

OthelloView.o: OthelloView.cpp OthelloView.h OthelloBoard.h View.h MyLib.h Class.h
	$(CPP) $(CPPFLAGS) -c OthelloView.cpp

OthelloDlg.o: OthelloDlg.cpp OthelloDlg.h OthelloBoard.h Dialog.h MyLib.h Class.h
	$(CPP) $(CPPFLAGS) -c OthelloDlg.cpp

PylosBoard.o: PylosBoard.cpp PylosMove.h PylosBoard.h MyLib.h Class.h
	$(CPP) $(CPPFLAGS) -c PylosBoard.cpp

PylosMove.o: PylosMove.cpp PylosMove.h PylosBoard.h MyLib.h Class.h
	$(CPP) $(CPPFLAGS) -c PylosMove.cpp

PylosView.o: PylosView.cpp PylosView.h PylosBoard.h View.h MyLib.h Class.h
	$(CPP) $(CPPFLAGS) -c PylosView.cpp

PylosDlg.o: PylosDlg.cpp PylosDlg.h PylosBoard.h Dialog.h MyLib.h Class.h
	$(CPP) $(CPPFLAGS) -c PylosDlg.cpp

CheckersBoard.o: CheckersBoard.cpp CheckersMove.h CheckersBoard.h MyLib.h Class.h
	$(CPP) $(CPPFLAGS) -c CheckersBoard.cpp

CheckersMove.o: CheckersMove.cpp CheckersMove.h CheckersBoard.h MyLib.h Class.h
	$(CPP) $(CPPFLAGS) -c CheckersMove.cpp

CheckersView.o: CheckersView.cpp CheckersView.h CheckersBoard.h View.h MyLib.h Class.h
	$(CPP) $(CPPFLAGS) -c CheckersView.cpp

CheckersDlg.o: CheckersDlg.cpp CheckersDlg.h CheckersBoard.h Dialog.h MyLib.h Class.h
	$(CPP) $(CPPFLAGS) -c CheckersDlg.cpp

.cpp.o:
	$(CPP) $(CPPFLAGS) -c $<
