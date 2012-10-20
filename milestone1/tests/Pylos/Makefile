HFILES=../../PylosMove.cpp ../../PylosBoard.cpp ../../Board.cpp

all: PylosTests

clean:
	rm *Test *.out

PylosTests: PylosMoveTest PylosBoardTest

PylosMoveTest:
	g++ PylosMoveTest.cpp $(HFILES) -o PylosMoveTest

PylosBoardTest:
	g++ -g PylosBoardTest.cpp $(HFILES) -o PylosBoardTest
