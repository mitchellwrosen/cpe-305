#!/bin/sh

make all

echo "foo.in"

echo "Checkers.0"
./BoardTest CheckersBoard < tests/milestone0_2/Checkers.0 > out1
./BoardTestClint CheckersBoard < tests/milestone0_2/Checkers.0 > out2
vimdiff out1 out2
rm out1 out2

echo "Checkers.1"
./BoardTest CheckersBoard < tests/milestone0_2/Checkers.1 > out1
./BoardTestClint CheckersBoard < tests/milestone0_2/Checkers.1 > out2
vimdiff out1 out2
rm out1 out2

echo "Checkers.2"
./BoardTest CheckersBoard < tests/milestone0_2/Checkers.2 > out1
./BoardTestClint CheckersBoard < tests/milestone0_2/Checkers.2 > out2
vimdiff out1 out2
rm out1 out2

echo "Checkers.3"
./BoardTest CheckersBoard < tests/milestone0_2/Checkers.3 > out1
./BoardTestClint CheckersBoard < tests/milestone0_2/Checkers.3 > out2
vimdiff out1 out2
rm out1 out2

echo "Checkers.4"
./BoardTest CheckersBoard < tests/milestone0_2/Checkers.4 > out1
./BoardTestClint CheckersBoard < tests/milestone0_2/Checkers.4 > out2
vimdiff out1 out2
rm out1 out2

echo "Checkers.5"
./BoardTest CheckersBoard < tests/milestone0_2/Checkers.5 > out1
./BoardTestClint CheckersBoard < tests/milestone0_2/Checkers.5 > out2
vimdiff out1 out2
rm out1 out2

echo "Pylos.0"
./BoardTest PylosBoard < tests/milestone0_2/Pylos.0 > out1
./BoardTestClint PylosBoard < tests/milestone0_2/Pylos.0 > out2
vimdiff out1 out2
rm out1 out2

echo "Pylos.1"
./BoardTest PylosBoard < tests/milestone0_2/Pylos.1 > out1
./BoardTestClint PylosBoard < tests/milestone0_2/Pylos.1 > out2
vimdiff out1 out2
rm out1 out2

echo "Pylos.2"
./BoardTest PylosBoard < tests/milestone0_2/Pylos.2 > out1
./BoardTestClint PylosBoard < tests/milestone0_2/Pylos.2 > out2
vimdiff out1 out2
rm out1 out2

echo "Pylos.3"
./BoardTest PylosBoard < tests/milestone0_2/Pylos.3 > out1
./BoardTestClint PylosBoard < tests/milestone0_2/Pylos.3 > out2
vimdiff out1 out2
rm out1 out2

echo "Pylos.4"
./BoardTest PylosBoard < tests/milestone0_2/Pylos.4 > out1
./BoardTestClint PylosBoard < tests/milestone0_2/Pylos.4 > out2
vimdiff out1 out2
rm out1 out2

echo "Pylos.5"
./BoardTest PylosBoard < tests/milestone0_2/Pylos.5 > out1
./BoardTestClint PylosBoard < tests/milestone0_2/Pylos.5 > out2
vimdiff out1 out2
rm out1 out2
exit

./BoardTest CheckersBoard < foo.in > out1
./BoardTestClint CheckersBoard < foo.in > out2
vimdiff out1 out2
rm out1 out2

./BoardTest OthelloBoard < foo.in > out1
./BoardTestClint OthelloBoard < foo.in > out2
vimdiff out1 out2
rm out1 out2

./BoardTest PylosBoard < foo.in > out1
./BoardTestClint PylosBoard < foo.in > out2
vimdiff out1 out2
rm out1 out2

echo "Checkers.0"
./BoardTest CheckersBoard < tests/milestone0/Checkers.0 > out1
./BoardTestClint CheckersBoard < tests/milestone0/Checkers.0 > out2
vimdiff out1 out2
rm out1 out2

echo "Checkers.1"
./BoardTest CheckersBoard < tests/milestone0/Checkers.1 > out1
./BoardTestClint CheckersBoard < tests/milestone0/Checkers.1 > out2
vimdiff out1 out2
rm out1 out2

echo "Checkers.2"
./BoardTest CheckersBoard < tests/milestone0/Checkers.2 > out1
./BoardTestClint CheckersBoard < tests/milestone0/Checkers.2 > out2
vimdiff out1 out2
rm out1 out2

echo "Checkers.3"
./BoardTest CheckersBoard < tests/milestone0/Checkers.3 > out1
./BoardTestClint CheckersBoard < tests/milestone0/Checkers.3 > out2
vimdiff out1 out2
rm out1 out2

echo "Checkers.4"
./BoardTest CheckersBoard < tests/milestone0/Checkers.4 > out1
./BoardTestClint CheckersBoard < tests/milestone0/Checkers.4 > out2
vimdiff out1 out2
rm out1 out2

echo "Checkers.5"
./BoardTest CheckersBoard < tests/milestone0/Checkers.5 > out1
./BoardTestClint CheckersBoard < tests/milestone0/Checkers.5 > out2
vimdiff out1 out2
rm out1 out2

echo "Pylos.0"
./BoardTest PylosBoard < tests/milestone0/Pylos.0 > out1
./BoardTestClint PylosBoard < tests/milestone0/Pylos.0 > out2
vimdiff out1 out2
rm out1 out2

echo "Pylos.1"
./BoardTest PylosBoard < tests/milestone0/Pylos.1 > out1
./BoardTestClint PylosBoard < tests/milestone0/Pylos.1 > out2
vimdiff out1 out2
rm out1 out2

echo "Pylos.2"
./BoardTest PylosBoard < tests/milestone0/Pylos.2 > out1
./BoardTestClint PylosBoard < tests/milestone0/Pylos.2 > out2
vimdiff out1 out2
rm out1 out2

echo "Pylos.3"
./BoardTest PylosBoard < tests/milestone0/Pylos.3 > out1
./BoardTestClint PylosBoard < tests/milestone0/Pylos.3 > out2
vimdiff out1 out2
rm out1 out2

echo "Pylos.4"
./BoardTest PylosBoard < tests/milestone0/Pylos.4 > out1
./BoardTestClint PylosBoard < tests/milestone0/Pylos.4 > out2
vimdiff out1 out2
rm out1 out2

echo "Pylos.5"
./BoardTest PylosBoard < tests/milestone0/Pylos.5 > out1
./BoardTestClint PylosBoard < tests/milestone0/Pylos.5 > out2
vimdiff out1 out2
rm out1 out2

