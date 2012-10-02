#!/usr/bin/python

import os

call = '~grade_cstaley/bin/turnin ~grade_cstaley/305/milestone0/turnin'

os.system('./gen.py')
for file in os.listdir('.'):
  if not file.endswith('.gen') and (
     file.startswith('Othello.') or
     file.startswith('Pylos.') or
     file.startswith('Checkers.')):
    call += ' %s' % file

os.system(call)
