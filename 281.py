LMT = 10**15

fac, last = [], 1
for i in range(1, 100):
    fac += [last]
    last *= i

def gcd(a, b):
    while a:
        a, b = b % a, a
    return b

def solve(m, n):
    ret = 0
    for i in range(1, m * n + 1):
        j = (m * n) / gcd(i, m * n)
        if n % j == 0:
            ret += fac[m * n / j] / fac[n / j]**m
    assert ret % (m * n) == 0
    return ret / (m * n)

ans = 0
for m in range(2, 100):
    for n in range(1, 100):
        last = n
        cur = solve(m, n)
        if cur > LMT:
            break
        print 'find: f(%d, %d) = %d' % (m, n, cur)
        ans += cur
    if last == 1:
        break
print ans
