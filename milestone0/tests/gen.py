#!/usr/bin/python

import os

for filename in os.listdir('.'):
  if filename.endswith('.gen'):
    genfile = open(filename)
    testfile = open(filename[:-4], 'w')
    for line in genfile:
      hash_index = line.find('#')
      if hash_index != -1:
        line = line[:hash_index] + '\n'
      if line.strip():
        if line == 'showAll\n':
          line = 'showBoard\nshowMove\nshowMoveHist\nshowVal\nkeyMoveCount\n'
        testfile.write(line)

    genfile.close()
    testfile.close()

