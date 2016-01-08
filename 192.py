from decimal import *
import math
from fractions import *

getcontext().prec = 200

bound = 10**12
n = 10**5
ans = 0

for i in range(1, n + 1):
    if i % 1000 == 0:
        print i

    if int(math.sqrt(i))**2 == i:
        continue

    x = Decimal(i)
    x = math.sqrt(x)
    us = [0, 1]
    vs = [1, 0]

    while True:
        t = int(math.floor(x))
        us += [us[-2] + us[-1] * t]
        vs += [vs[-2] + vs[-1] * t]
        if vs[-1] > bound:
            tt = (bound - vs[-2]) / vs[-3]
            ans += tt * vs[-3] + vs[-2]
            # print "%d: %d/%d" % (i, us[-3] + us[-2] * tt, vs[-3] + vs[-2] * tt)
            break
        x = 1 / (x - t)

print 'ans = %d' % (ans)
