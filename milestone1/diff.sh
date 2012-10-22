#!/bin/sh

make BoardTest
./BoardTest < tests/Pylos.2 > out1
./BoardTestClint PylosBoard < tests/Pylos.2 > out2
vimdiff out1 out2
rm out1 out2
