n = 10**15

import sage.all as _

def solve(n, MOD):
    R = _.Integers(MOD)
    U = _.matrix(R, [[11, -1], [1, 0]])
    V = _.matrix(R, [[2], [11]])
    ans = U**(pow(2, n, MOD * MOD - 1)) * V
    return (ans[0][0] - 5) / 6

cdef int isp(long n):
print n
cdef int i = 2
    while i * i <= n:
        if n % i == 0:
            return 0
    return 1

# print solve(100 - 1, 1000000007)
lx = 0
ans = 0
end = 10**9 + 10**7
cur = 10**9
while cur < end:
    print cur
    if isp(cur) == 0:
        continue
    if cur > lx:
        print cur
        lx = cur + 10**5
        #         print x
    ans += int(solve(n - 1, cur))
    print ans
