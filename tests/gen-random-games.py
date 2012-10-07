#!/usr/bin/python

import os
import random
import sys

###########################################################
# Othello.0.gen
###########################################################
with open('Othello.0.gen', 'w') as genfile:
  genfile.write('showAll\n')

  genfile.write('# Bunch of bad enterMoves\n')
  for s1 in ['', '[']:
    for s2 in ['', '2', '  2  ']:
      for s3 in ['', ',', '  ,  ']:
        for s4 in ['', '2', '  2  ']:
          for s5 in ['', ']', '  ]  ']:
            genfile.write('enterMove  %s%s%s%s%s\n' % (s1, s2, s3, s4, s5))
  genfile.write('enterMove [2,2] foo\n')

  genfile.write('\n# Bunch of attempted buffer overflows\n')
  for command in ['enterMove', 'saveBoard', 'loadBoard', 'saveMove',
                  'loadMove', 'compareKeys', 'compareMove']:
    genfile.write('%s %s\n' % (command, 'a' * 5000))
  genfile.write('showOptions\n')
  genfile.write('%s\n' % ('a' * 5000))

  genfile.write('\n# Bunch of compareMoves\n')
  for row1 in [-1, 2, 5, 8]:
    for col1 in [-1, 2, 5, 8]:
      genfile.write('enterMove [%s,%s]\n' % (row1, col1))
      if row1 in xrange(8) and col1 in xrange(8):
        for row2 in xrange(8):
          for col2 in xrange(8):
            genfile.write('compareMove [%s,%s]\n' % (row2, col2))
        genfile.write('compareMove Pass\n')

  genfile.write('quit\n')

###########################################################
# Othello.1.gen
###########################################################
with open('Othello.1.gen', 'w') as genfile:
  genfile.write('\n# Play quick games\n')
  games = 15
  for i in xrange(games):
    genfile.write('showAll\n')
    genfile.write('testRun %d 20\n' % (i*2000))
    genfile.write('saveBoard b%s\n' % i)
    genfile.write('saveMove m%s\n' % i)

  genfile.write('\n# Compare keys of all saved boards.\n')
  for i in xrange(games):
    genfile.write('loadBoard b%s\n' % i)
    genfile.write('showAll\n')
    for j in xrange(games):
      genfile.write('compareKeys b%s\n' % j)
    genfile.write('undoLastMove 30\n')
    genfile.write('showAll\n')
    for j in xrange(games):
      genfile.write('compareKeys b%s\n' % j)

  genfile.write('\n# Load saved moves and show them.\n')
  for i in xrange(games):
    genfile.write('loadMove m%s\n' % i)
    genfile.write('showAll\n')
    genfile.write('applyMove\n')
    genfile.write('showAll\n')

  genfile.write('quit\n')

################################################################################
# Othello.2.gen
################################################################################
with open('Othello.2.gen', 'w') as genfile:
  games = 17
  for i in xrange(games):
    genfile.write('setOptions\nyfoo\n')
    for j in xrange(4):
      genfile.write('%s\n' % ('1' * 5000))
      genfile.write('-1\n101\n[1]\n1.5\n1 foo\n%d\n' % random.randint(0, 100))
    genfile.write('testRun %d 300\n' % (i * 2345))
    genfile.write('showAll\n')

  for i in xrange(games):
    genfile.write('saveBoard b%d\n' % i)
    genfile.write('setOptions\ny\n')
    for j in xrange(4):
      genfile.write('%d\n' % random.randint(0, 100))

  for i in xrange(games):
    genfile.write('loadBoard b%d\n' % i)
    for j in xrange(games):
      genfile.write('compareKeys b%d\n' % j)

  genfile.write('quit\n')

################################################################################
# Pylos.0.gen
################################################################################
with open('Pylos.0.gen', 'w') as genfile:
  genfile.write('showAll\n')

  genfile.write('# Bunch of bad enterMoves\n')
  for s1 in ['', '[']:
    for s2 in ['', ',']:
      for s3 in ['', ']']:
        genfile.write('enterMove  Play  at  %s0%s0%s\n' % (s1, s2, s3))
  for s1 in ['', ' ', 'taking']:
    for s2 in ['', '[']:
      for s3 in ['', ',']:
        for s4 in ['', ']']:
          genfile.write('enterMove  Play at [0,0]%s%s1%s1%s\n' % (s1, s2, s3, s4))
  for s1 in ['', ' ', 'and']:
    for s2 in ['', '[']:
      for s3 in ['', ',']:
        for s4 in ['', ']']:
          genfile.write('enterMove  Play at [0,0] taking [1,1]%s%s2%s2%s\n' % (s1, s2, s3, s4))
  for s1 in ['', '[']:
    for s2 in ['', ',']:
      for s3 in ['', ']']:
        for s4 in ['', ' ', 'to']:
          for s5 in ['', '[']:
            for s6 in ['', ',']:
              for s7 in ['', ']']:
                genfile.write('enterMove  Promote  from  %s0%s0%s%s%s1%s1%s\n' % (s1, s2, s3, s4, s5, s6, s7))
  for s1 in ['', ' ', 'taking']:
    for s2 in ['', '[']:
      for s3 in ['', ',']:
        for s4 in ['', ']']:
          genfile.write('enterMove  Promote from [0,0] to [1,1]%s%s2%s2%s\n' % (s1, s2, s3, s4))
  for s1 in ['', ' ', 'and']:
    for s2 in ['', '[']:
      for s3 in ['', ',']:
        for s4 in ['', ']']:
          genfile.write('enterMove  Promote from [0,0] to [1,1] taking [2,2]%s%s3%s3%s\n' % (s1, s2, s3, s4))

  genfile.write('\n# Bunch of attempted buffer overflows\n')
  for command in ['enterMove', 'saveBoard', 'loadBoard', 'saveMove',
                  'loadMove', 'compareKeys', 'compareMove']:
    genfile.write('%s %s\n' % (command, 'a' * 5000))
  genfile.write('showOptions\n')
  genfile.write('%s\n' % ('a' * 5000))

  genfile.write('\n# Bunch of bad enterMoves\n')
  genfile.write('enterMove Pl ay  at [0,0]\n')
  genfile.write('enterMove Play  a t [0,0]\n')
  genfile.write('enterMove Play  at [0,0] tak ing [1,1]\n')
  genfile.write('enterMove Play  at [0,0] taking [1,1] an d [2,2]\n')
  genfile.write('enterMove Pro mote from [0,0] to [1,1]\n')
  genfile.write('enterMove Promote fr om [0,0] to [1,1]\n')
  genfile.write('enterMove Promote from [0,0] to [1,1] tak ing [2,2]\n')
  genfile.write('enterMove Promote from [0,0] to [1,1] taking [2,2] an d [3,3]\n')

  genfile.write('\n# Bunch of compareMoves\n')
  for move in ['Play at [1,1]', 'Play at [1,1] taking [1,1]', 'Play at [1,1] taking [1,1] and [1,1]',
               'Promote from [1,1] to [1,1]', 'Promote from [1,1] to [1,1] taking [1,1]',
               'Promote from [1,1] to [1,1] taking [1,1] and [1,1]']:
    genfile.write('enterMove %s\n' % move)
    for row1 in xrange(3):
      for col1 in xrange(3):
        genfile.write('compareMove Play at [%s,%s]\n' % (row1, col1))
        for i in xrange(3):
          genfile.write('compareMove Play at [%s,%s] taking [%s,%s]\n' % (row1, col1, i, i))
          genfile.write('compareMove Promote from [%s,%s] to [%s,%s]\n' % (row1, col1, i, i))
          genfile.write('compareMove Play at [%s,%s] taking [%s,%s] and [%s,%s]\n' % (row1, col1, i, i, i, i))
          genfile.write('compareMove Promote from [%s,%s] to [%s,%s] taking [%s,%s]\n' % (
              row1, col1, i, i, i, i))

################################################################################
# Pylos.1.gen
################################################################################
with open('Pylos.1.gen', 'w') as genfile:
  genfile.write('\n# Play quick games\n')
  for i in xrange(13):
    genfile.write('showAll\n')
    genfile.write('testRun %d 20\n' % (i*2000))
  genfile.write('quit\n')

################################################################################
# Pylos.2.gen
################################################################################
with open('Pylos.2.gen', 'w') as genfile:
  genfile.write('\n# Compare keys of all saved boards.\n')
  games = 9

  for i in xrange(games):
    genfile.write('testRun %d 30\n' % (i*3000))
    genfile.write('saveBoard b%s\n' % i)
    genfile.write('saveMove m%s\n' % i)

  for i in xrange(games):
    genfile.write('loadBoard b%s\n' % i)
    genfile.write('showAll\n')
    for j in xrange(games):
      genfile.write('compareKeys b%s\n' % j)
    genfile.write('undoLastMove 30\n')
    for j in xrange(games):
      genfile.write('compareKeys b%s\n' % j)

  genfile.write('\n# Load saved moves and show them.\n')
  for i in xrange(games):
    genfile.write('loadMove m%s\n' % i)
    genfile.write('showAll\n')
    genfile.write('applyMove\n')
    genfile.write('showAll\n')
  genfile.write('quit\n')

################################################################################
# Pylos.3.gen
################################################################################
with open('Pylos.3.gen', 'w') as genfile:
  games = 16
  for i in xrange(games):
    genfile.write('setOptions\nyfoo\n')
    marbleWeight = random.randint(0, 1000)

    # 1-1000
    genfile.write('%s\n' % ('1' * 5000))
    genfile.write('-1\n101\n[1]\n1.5\n1 foo\n%d\n' % marbleWeight)

    # >= 0, < marbleWeight
    genfile.write('%s\n' % ('1' * 5000))

    genfile.write('-1\n[1]\n1.5\n1 foo\n%d\n%d\n%d\n' % (marbleWeight+1,
        marbleWeight, marbleWeight-1))

    # >= 0, < marbleWeight, even
    genfile.write('%s\n' % ('1' * 5000))
    genfile.write('-1\n[2]\n2.5\n2 foo\n%d\n%d\n%d\n%d\n' % (
        marbleWeight+1, marbleWeight, marbleWeight-1, marbleWeight-2))

    genfile.write('testRun %d 300\n' % (i * 3456))
    genfile.write('showAll\n')

  for i in xrange(games):
    genfile.write('saveBoard b%d\n' % i)
    genfile.write('setOptions\ny\n')
    marbleWeight = random.randint(0, 1000)
    genfile.write('%d\n' % marbleWeight)
    genfile.write('%d\n' % random.randint(0, marbleWeight-1))
    freeWeight = random.randint(0, marbleWeight-1)
    if freeWeight % 2 == 1:
      freeWeight -= 1
    genfile.write('%d\n' % freeWeight)

  for i in xrange(games):
    genfile.write('loadBoard b%d\n' % i)
    for j in xrange(games):
      genfile.write('compareKeys b%d\n' % j)

  genfile.write('quit\n')

################################################################################
# Checkers.0.gen
################################################################################
with open('Checkers.0.gen', 'w') as genfile:
  genfile.write('showAll\n')

  genfile.write('# Bunch of bad enterMoves\n')
  for s1 in 'aHi':
    for s2 in ' 089':
      for s3 in ['', '->']:
        for s4 in 'aHi':
          for s5 in ' 089':
            genfile.write('enterMove  %s%s%s%s%s\n' % (s1, s2, s3, s4, s5))
  for s1 in ['', '->', '  ->  ']:
    for s2 in 'aHi':
      for s3 in ' 089':
        genfile.write('enterMove  a1->a1%s%s%s\n' % (s1, s2, s3))
  genfile.write('enterMove a1->a2 foo')

  genfile.write('\n# Bunch of attempted buffer overflows\n')
  for command in ['enterMove', 'saveBoard', 'loadBoard', 'saveMove',
                  'loadMove', 'compareKeys', 'compareMove']:
    genfile.write('%s %s\n' % (command, 'a' * 5000))

  genfile.write('\n# Bunch of compareMoves\n')
  for s1 in ['a1', 'd2', 'h1']:
    for s2 in ['a1', 'd2', 'h1']:
      genfile.write('enterMove %s->%s\n' % (s1, s2))
      for s5 in 'ach':
        for s6 in '157':
          for s7 in 'bdH':
            for s8 in '128':
              genfile.write('compareMove %s%s->%s%s\n' % (s5, s6, s7, s8))

  genfile.write('quit\n')

###########################################################
# Checkers.1.gen
###########################################################
with open('Checkers.1.gen', 'w') as genfile:
  genfile.write('\n# Play quick games\n')
  for i in xrange(43):
    genfile.write('showAll\n')
    genfile.write('testRun %d 20\n' % (i*2000))
  genfile.write('quit\n')

###########################################################
# Checkers.2.gen
###########################################################
with open('Checkers.2.gen', 'w') as genfile:
  genfile.write('\n# Compare keys of all saved boards.\n')
  games = 9

  for i in xrange(games):
    genfile.write('testRun %d 30\n' % (i*3000))
    genfile.write('saveBoard b%s\n' % i)
    genfile.write('saveMove m%s\n' % i)

  for i in xrange(games):
    genfile.write('loadBoard b%s\n' % i)
    genfile.write('showAll\n')
    for j in xrange(games):
      genfile.write('compareKeys b%s\n' % j)
    genfile.write('undoLastMove 30\n')
    genfile.write('showAll\n')
    for j in xrange(games):
      genfile.write('compareKeys b%s\n' % j)

  genfile.write('\n# Load saved moves and show them.\n')
  for i in xrange(games):
    genfile.write('loadMove m%s\n' % i)
    genfile.write('showAll\n')
    genfile.write('applyMove\n')
    genfile.write('showAll\n')

  genfile.write('\n# Finish off with some testRuns\n')
  for i in xrange(13):
    genfile.write('testRun %d 10\n' % (i*1234))
    genfile.write('showAll\n')

  genfile.write('quit\n')

################################################################################
# Checkers.3.gen
################################################################################
with open('Checkers.3.gen', 'w') as genfile:
  games = 16
  for i in xrange(games):
    genfile.write('setOptions\nyfoo\n')

    # 1-5000
    genfile.write('%s\n' % ('1' * 5000))
    genfile.write('-1\n101\n[1]\n1.5\n1 foo\n%d\n' % random.randint(0, 1000))

    # >= 0, < marbleWeight
    genfile.write('%s\n' % ('1' * 5000))
    genfile.write('-1\n101\n[1]\n1.5\n1 foo\n%d\n' % random.randint(0, 1000))

    # >= 0, < marbleWeight, even
    genfile.write('%s\n' % ('1' * 5000))
    genfile.write('-1\n101\n[1]\n1.5\n1 foo\n%d\n' % random.randint(0, 100))

    genfile.write('testRun %d 300\n' % (i * 4567))
    genfile.write('showAll\n')

  for i in xrange(games):
    genfile.write('saveBoard b%d\n' % i)
    genfile.write('setOptions\ny\n')
    genfile.write('%d\n' % random.randint(0, 1000))
    genfile.write('%d\n' % random.randint(0, 1000))
    genfile.write('%d\n' % random.randint(0, 100))

  for i in xrange(games):
    genfile.write('loadBoard b%d\n' % i)
    for j in xrange(games):
      genfile.write('compareKeys b%d\n' % j)

  genfile.write('quit\n')

###########################################################
# Generate *.4.gen (testPlay)
# Generate *.5.gen (testRun)
###########################################################

games = ['Othello', 'Pylos', 'Checkers']
playIters = [180, 60, 115]
runIters = [240, 60, 130]

for i in xrange(len(games)):
  with open('%s.4.gen' % games[i], 'w') as genfile:
    genfile.write('# Play a bunch of games, automatically generated by '
                  'gen-random-games.py\n')
    for seed in xrange(playIters[i]):
      genfile.write('testPlay %s 500\n' % seed)
      genfile.write('showAll\n')
      genfile.write('undoLastMove 500\n\n')

    genfile.write('quit\n')

  with open('%s.5.gen' % games[i], 'w') as genfile:
    genfile.write('# Run a bunch of games, automatically generated by '
                  'gen-random-games.py\n')
    for seed in xrange(runIters[i]):
      genfile.write('testRun %s 50\n' % seed)
      genfile.write('showAll\n')

    genfile.write('quit\n')

os.system('./gen.py')
