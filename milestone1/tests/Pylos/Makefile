HFILES=../Test.h ../../PylosMove.cpp ../../Board.cpp

all: clean PylosTests

clean:
	rm *Test *.out

PylosTests: PylosMoveTest PylosBoardTest

PylosMoveTest:
	g++ PylosMoveTest.cpp $(HFILES) -o PylosMoveTest

PylosBoardTest:
	g++ PylosBoardTest.cpp $(HFILES) -o PylosBoardTest
