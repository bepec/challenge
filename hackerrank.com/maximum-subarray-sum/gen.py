import sys
import os
import random


if len(sys.argv) < 3:
    print "Usage: {} N M [MAX]".format(sys.argv[0])
    exit(1)

n = int(sys.argv[1])
m = int(sys.argv[2])
vmax = int(sys.argv[3] if len(sys.argv) > 3 else 10**18)

if n < 2 or n > 10e5:
    n = 10**5
if m < 2 or m > 10e14:
    m = 10**14

random.seed()

print n, m
line = ""
for i in range(0,n):
    line = line + str(random.randint(1, vmax)) + " "
print line
