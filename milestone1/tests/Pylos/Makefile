
all: clean PylosTest

clean:
	rm PylosTest PylosMove.out 2>/dev/null

PylosTest:
	g++ PylosTest.cpp ../Test.h ../../PylosMove.cpp ../../Board.cpp -o PylosTest
