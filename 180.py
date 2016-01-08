from fractions import *
import math

k = 35
Q = set([Fraction(a, b) for b in range(k + 1) for a in range(1, b)])
print 'len(Q) = %d' % len(Q)

def f1(n, x, y, z):
    return x**(n + 1) + y**(n + 1) - z**(n + 1)

def f2(n, x, y, z):
    return (x * y + y * z + z * x) * (x**(n - 1) + y**(n - 1) - z**(n - 1))

def f3(n, x, y, z):
    return x * y * z * (x**(n - 2) + y**(n - 2) - z**(n - 2))

def ff(n, x, y, z):
    return f1(n, x, y, z) + f2(n, x, y, z) - f3(n, x, y, z)

def gg(n, x, y, z):
    return (x + y + z) * (x**n + y**n - z**n)

def root(t, p):
    if p < 0:
        return root(1 / t, -p)
    a, b = t.numerator, t.denominator
    sa, sb = int(math.pow(a + 0.1, 1. / p)), int(math.pow(b + 0.1, 1. / p))
    if sa > 0 and sb > 0 and Fraction(sa, sb)**p == t:
        return Fraction(sa, sb)
    return 0

F = {}
t = 0
for x in Q:
    for y in Q:
        if x > y:
            continue
        for p in [-2, -1, 1, 2]:
            z = root(x**p + y**p, p)
            if z in Q:
                # print ff(p, x, y, z), gg(p, x, y, z)
                F[x + y + z] = True

t = 0
for x in F.keys():
    t += x
print "t = %s, ans = %d" % (t, t.numerator + t.denominator)
