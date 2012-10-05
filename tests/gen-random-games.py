#!/usr/bin/python

import os
import sys

###########################################################
# Othello.0.gen
###########################################################
with open('Othello.test.gen', 'w') as genfile:
  genfile.write('showAll\n')

  genfile.write('# Bunch of bad enterMoves\n')
  for s1 in ['', '[', '  [  ']:
    for s2 in ['', '2', '  2  ']:
      for s3 in ['', ',', '  ,  ']:
        for s4 in ['', '2', '  2  ']:
          for s5 in ['', ']', '  ]  ']:
            genfile.write('enterMove  %s%s%s%s%s\n' % (s1, s2, s3, s4, s5))
  genfile.write('enterMove [2,2] foo\n')
  
  genfile.write('\n# Bunch of attempted buffer overflows\n')
  for command in ['enterMove', 'saveBoard', 'loadBoard', 'saveMove', 
                  'loadMove', 'compareKeys', 'compareMove']:
    genfile.write('%s %s\n' % (command, 'a' * 1000)) 

  genfile.write('\n# Bunch of compareMoves\n')
  for row1 in [x-1 for x in xrange(9)]:
    for col1 in [x-1 for x in xrange(9)]:
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
with open('Othello.test1.gen', 'w') as genfile:
  genfile.write('\n# Play quick games\n')
  games = 20
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

###########################################################
# Pylos.0.gen
###########################################################
with open('Pylos.test.gen', 'w') as genfile:
  genfile.write('showAll\n')

  genfile.write('# Bunch of bad enterMoves\n')
  for s1 in ['', '[', '  [  ']:
    for s2 in ['', ',', '  ,  ']:
      for s3 in ['', ']', '  ]  ']:       
        genfile.write('enterMove  Play  at  %s0%s0%s\n' % (s1, s2, s3))
  for s1 in ['', 'taking', '  taking  ']:
    for s2 in ['', '[', '  [  ']:
      for s3 in ['', ',', '  ,  ']:
        for s4 in ['', ']', '  ]  ']:       
          genfile.write('enterMove  Play at [0,0]%s%s1%s1%s\n' % (s1, s2, s3, s4))
  for s1 in ['', 'and', '  and  ']:
    for s2 in ['', '[', '  [  ']:
      for s3 in ['', ',', '  ,  ']:
        for s4 in ['', ']', '  ]  ']:       
          genfile.write('enterMove  Play at [0,0] taking [1,1]%s%s2%s2%s\n' % (s1, s2, s3, s4))
  for s1 in ['', '[', '  [  ']:
    for s2 in ['', ',', '  ,  ']:
      for s3 in ['', ']', '  ]  ']:       
        for s4 in ['', 'to', '  to  ']:
          for s5 in ['', '[', '  [  ']:
            for s6 in ['', ',', '  ,  ']:
              for s7 in ['', ']', '  ]  ']:
                genfile.write('enterMove  Promote  from  %s0%s0%s%s%s1%s1%s\n' % (s1, s2, s3, s4, s5, s6, s7))
  for s1 in ['', 'taking', '  taking  ']:
    for s2 in ['', '[', '  [  ']:
      for s3 in ['', ',', '  ,  ']:
        for s4 in ['', ']', '  ]  ']:       
          genfile.write('enterMove  Promote from [0,0] to [1,1]%s%s2%s2%s\n' % (s1, s2, s3, s4))
  for s1 in ['', 'and', '  and  ']:
    for s2 in ['', '[', '  [  ']:
      for s3 in ['', ',', '  ,  ']:
        for s4 in ['', ']', '  ]  ']:       
          genfile.write('enterMove  Promote from [0,0] to [1,1] taking [2,2]%s%s3%s3%s\n' % (s1, s2, s3, s4))

  genfile.write('\n# Bunch of attempted buffer overflows\n')
  for command in ['enterMove', 'saveBoard', 'loadBoard', 'saveMove', 
                  'loadMove', 'compareKeys', 'compareMove']:
    genfile.write('%s %s\n' % (command, 'a' * 1000)) 

  genfile.write('quit\n')

###########################################################
# Pylos.1.gen
###########################################################
with open('Pylos.test1.gen', 'w') as genfile:
  genfile.write('\n# Bunch of bad enterMoves\n')
  # TODO

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
          for j in xrange(3):
            genfile.write('compareMove Play at [%s,%s] taking [%s,%s] and [%s,%s]\n' % (
                row1, col1, i, i, j, j))
            genfile.write('compareMove Promote from [%s,%s] to [%s,%s] taking [%s,%s]\n' % (
                row1, col1, i, i, j, j))
            for k in xrange(3):
              genfile.write('compareMove Promote from [%s,%s] to [%s,%s] taking [%s,%s] and [%s,%s]\n' % (
                  row1, col1, i, i, j, j, k, k))
            
  """
  for move in ['Play at [1,1]', 'Play at [1,1] taking [1,2]', 
               'Play at [1,1] taking [1,2] and [2,1]',
               'Promote from [1,1] to [2,2]', 
               'Promote from [1,1] to [2,2] taking [1,3]',
               'Promote from [1,1] to [2,2] taking [1,3] and [3,3]']:
    genfile.write('enterMove %s\n' % move)
    for row1 in xrange(4):
      for col1 in xrange(4):
        genfile.write('compareMove Play at [%s,%s]\n' % (row1, col1))
        for row2 in xrange(4):
          for col2 in xrange(4):
            genfile.write('compareMove Play at [%s,%s] taking [%s,%s]\n' % (row1, col1, row2, col2))
            genfile.write('compareMove Promote from [%s,%s] to [%s,%s]\n' % (row1, col1, row2, col2))
            for row3 in xrange(4):
              for col3 in xrange(4):
                genfile.write('compareMove Play at [%s,%s] taking [%s,%s] and [%s,%s]\n' % (
                    row1, col1, row2, col2, row3, col3))
                genfile.write('compareMove Promote from [%s,%s] to [%s,%s] taking [%s,%s]\n' % (
                    row1, col1, row2, col2, row3, col3))
                for row4 in xrange(4):
                  for col4 in xrange(4):
                    genfile.write('compareMove Promote from [%s,%s] to [%s,%s] taking [%s,%s] and [%s,%s]\n' % (
                        row1, col1, row2, col2, row3, col3, row4, col4))


  """

  """
  genfile.write('\n# Play 10 quick games\n')
  for i in xrange(10):
    genfile.write('showAll\n')
    genfile.write('testRun %d 20\n' % (i*2000))
    genfile.write('saveBoard b%s\n' % i)
    genfile.write('saveMove m%s\n' % i)

  genfile.write('\n# Compare keys of all saved boards.\n')
  for i in xrange(10):
    genfile.write('loadBoard b%s\n' % i)
    genfile.write('showAll\n')
    for j in xrange(10):
      genfile.write('compareKeys b%s\n' % j)
    genfile.write('undoLastMove 30\n')
    genfile.write('showAll\n')
    for j in xrange(10):
      genfile.write('compareKeys b%s\n' % j)

  genfile.write('\n# Load saved moves and show them.\n')
  for i in xrange(10):
    genfile.write('loadMove m%s\n' % i)
    genfile.write('showAll\n')
    genfile.write('applyMove\n')
    genfile.write('showAll\n')
  """
  genfile.write('quit\n')

###########################################################
# Generate *.5.gen (testPlay)
# Generate *.6.gen (testRun)
###########################################################

games = ['Othello', 'Pylos', 'Checkers']
playIters = [180, 60, 115]
runIters = [240, 60, 130]

for i in xrange(len(games)):
  with open('%s.5.gen' % games[i], 'w') as genfile:
    genfile.write('# Play a bunch of games, automatically generated by '
                  'gen-random-games.py\n')
    for seed in xrange(playIters[i]):
      genfile.write('testPlay %s 500\n' % seed)
      genfile.write('showAll\n')
      genfile.write('undoLastMove 500\n\n')

    genfile.write('quit\n')

  with open('%s.6.gen' % games[i], 'w') as genfile:
    genfile.write('# Run a bunch of games, automatically generated by '
                  'gen-random-games.py\n')
    for seed in xrange(runIters[i]):
      genfile.write('testRun %s 50\n' % seed)
      genfile.write('showAll\n')

    genfile.write('quit\n')

os.system('./gen.py')
