import sys
import random

MAXGEN = 10000  #maximum words generated
NPREF = 2       #number of prefix words
NONWORD = '\n'

s = sys.stdin.read()
l = s.split()
statetab = {}
prefix = (NONWORD,) * NPREF

for word in l:
    if prefix in statetab:
        statetab[prefix].append(word)
    else:
        statetab[prefix] = [word]
    prefix = prefix[1:] + (word,)

if prefix in statetab:
    statetab[prefix].append(NONWORD)
else:
    statetab[prefix] = [NONWORD]

prefix = (NONWORD,) * NPREF
for i in xrange(MAXGEN):
    word = random.choice(statetab[prefix])
    if word == NONWORD:
        break
    print word,
    prefix = prefix[1:] + (word,)  

