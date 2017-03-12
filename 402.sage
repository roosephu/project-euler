%%cython

import sage.all as _

cdef int GCD(int a, int b):
    if a:
        return GCD(b % a, a)
    return b

cdef int M(int a, int b, int c):
    cdef int T = 0
    for i in xrange(25):
        s = (((i + a) * i + b) * i + c) * i
        T = GCD(T, s)
    return T

cdef int N = 200
cdef int P = 24
cdef int L = 7
cdef int a, b, c
E = 1234567890123
mx = [0] * 2000
polys = [0] * P

for a in range(1, N + 1):
    for b in range(1, N + 1):
        for c in range(1, N + 1):
            mx[max([a, b, c])] += M(a, b, c)
#             if a <= 5 and b <= 5 and c <= 5:
#                 print a, b, c, M(a, b, c)
for i in range(N):
    mx[i + 1] += mx[i]
print 'finished'

def findRecurrence(m):
    if E < m:
        return 0

    modulo = _.fibonacci(m) % P
    ws = []
    acc = 0
    for i in range(50):
        w = _.fibonacci(i * P + m) // P
        acc += polys[modulo](x=w)
        ws += [acc]

    charpoly = _.berlekamp_massey(ws)
    print charpoly #, ws

    x = _.var('x')
    R = _.PolynomialRing(_.Integers(10**9), 'x')
    F = R.quo(charpoly)
    result = F.gen()**((E - m) // P)
    print result, ws[0]
    ret = 0
    for x, y in zip(list(result), ws):
        ret += int(x) * int(y)
    return ret

for a in range(P):
    polys[a] = _.PolynomialRing(_.QQ, 'x').lagrange_polynomial([(i, mx[i * P + a]) for i in range(L)])

# bf = 0
# for i in range(2, 100 + 1):
#     e = _.fibonacci(i)
#     bf += polys[e % P](x=e // P)
# print bf

ans = 0
for i in range(P):
    ans += findRecurrence(i + 2)
print 'ans = %d' % (ans,)