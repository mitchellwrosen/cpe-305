#!/usr/bin/python

import os

for filename in os.listdir('.'):
  if filename.endswith('.gen'):
    genfile = open(filename)
    infile = open(filename[:-4], 'w')
    for line in genfile:
      if not line.startswith('#'):
        infile.write(line)

    genfile.close()
    infile.close()

