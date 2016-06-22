def solve(n):
    if n == 0:
        return 0
    return n // 2 + solve(n // 2)

m = 904961
N = 10^12

print 'ans = %d' % (solve(N // 2) + m * ((N + 1) // 4 + solve((N + 1) // 4)))
