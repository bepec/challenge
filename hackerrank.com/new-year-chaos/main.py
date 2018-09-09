import sys
import os
from functools import reduce

def test():
    sys.stdin.readline()
    queue = [int(n) for n in sys.stdin.readline().split()]
    bribe = [0 for n in queue] + [0]
    good = False
    while not good:
        good = True
        for i in range(1, len(queue)):
            cur, prev = queue[i], queue[i-1]
            if cur < prev:
                # print("bribe: {} before {}".format(prev, cur))
                good = False
                if bribe[prev] == 2:
                    return -1
                bribe[prev] += 1
                queue[i], queue[i-1] = prev, cur
    return reduce(lambda x, y: x + y, bribe)

t = int(sys.stdin.readline().rstrip())
for i in range(0, t):
    result = test()
    print("Too chaotic") if result == -1 else print(result)
