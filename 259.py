from fractions import *
from itertools import *

n = 9

f = [[set() for i in range(n + 1)] for j in range(n + 1)]

for l in reversed(range(n + 1)):
    for r in range(l + 1, n + 1):
        tmp = [Fraction(reduce(lambda x, y: x * 10 + y, range(1, n + 1)[l:r]))]
        for k in range(l, r):
            print '[%d, %d] <= |%d| * |%d|' % (l, r, len(f[l][k]), len(f[k][r]))
            for a in f[l][k]:
                for b in f[k][r]:
                    tmp += [a + b]
                    tmp += [a - b]
                    tmp += [a * b]
                    if b != 0:
                        tmp += [a / b]

        f[l][r] = set(tmp)
        print "l = %d, r = %d, f[l, r].size = %d" % (l, r, len(f[l][r]))

ans = 0
for v in f[0][n]:
    if v == int(v) and v > 0:
        ans += int(v)
print 'ans = %d' % ans
