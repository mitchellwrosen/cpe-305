#!/bin/sh

make all
./BoardTest PylosBoard < tests/milestone0/Pylos.0 > out1
./BoardTestClint PylosBoard < tests/milestone0/Pylos.0 > out2
#./BoardTest CheckersBoard < tests/milestone0/Checkers.0 > out1
#./BoardTestClint CheckersBoard < tests/milestone0/Checkers.0 > out2
#./BoardTest CheckersBoard < foo.in > out1
#./BoardTestClint CheckersBoard < foo.in > out2
vimdiff out1 out2
rm out1 out2
