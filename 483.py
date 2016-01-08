from math import *
from fractions import gcd

def is_prime(n):
    i = 2
    while i * i <= n:
        if n % i == 0:
            return False
        i += 1
    return True

def update(l, x):
    # print x
    for i in range(len(l)):
        v = l[i]
        if v < x:
            l[i], x = x, v
        else:
            break
    return l

def LCM(a, b):
    return a * b // gcd(a, b)

def count(n, L):
    print 'counting: %d' % (L)
    g = [{1: 1} if x == 0 else {} for x in range(n + 1)]
    for i in range(n): # old total length
        print 'len(g[%d]) = %d' % (i, len(g[i]))
        for old_lcm, nums in g[i].iteritems():
            # print old_lcm, f[n - i][0], L
            if old_lcm * f[n - i][0] < L: # cannot get total LCM = L
                continue

            for j in range(1, n - i + 1): # new segment length
                if L % j == 0:
                    new_len, new_lcm = i + j, LCM(old_lcm, j)
                    if new_lcm not in g[new_len]:
                        g[new_len][new_lcm] = g[i][old_lcm]
                    else:
                        g[new_len][new_lcm] += g[i][old_lcm]
    print g[n]
    return g[n][L]

n = 350
f = [[1] * 5 for i in range(n + 10)]
for i in range(2, n + 1):
    if is_prime(i):
        print i
        for j in range(n, 0, -1):
            x = i
            while x <= j:
                for val in f[j - x]:
                    update(f[j], val * x)
                x *= i

print f[n] # [exp(x) for x in f[n]]
for lcm in f[n]:
    print 'count for %d = %d' % (lcm, count(n, lcm))
