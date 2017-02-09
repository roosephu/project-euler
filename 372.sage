M, N = 2 * 10^6, 10^9

def bf(n, k, b):
    ret = 0
    for i in xrange(1, n + 1):
        v = k * i + b
        u = floor(v)
        ret += u
    return ret

def dfs(n, k, b):
#     print n, k, b
    if n == 0:
        return 0
    if k == 0:
        return n * floor(b)

    if floor(b) != 0:
        nb = floor(b)
        return dfs(n, k, b - nb) + nb * n

    if k >= 1:
        nk = floor(k)
        return dfs(n, k - nk, b) + nk * n * (n + 1) // 2
    y = floor(k * n + b)
    return y * n - dfs(y, (1 / k), (-b / k))

def solve(n, m, k):
    pos = floor(m / k)
    if pos > n:
        return dfs(n, k, 0)
    return dfs(pos, k, 0) + (n - pos) * m

def calc(k):
    k = k.n(150)
#     print k, solve(N, N, k), solve(N, M, k), solve(M, N, k), solve(M, M, k)
    return solve(N, N, k) - solve(N, M, k) - solve(M, N, k) + solve(M, M, k)

eps = 1 / (N + 1)^2
# print calc(sqrt(9803 + 1 - eps)) - calc(sqrt(9803 - eps))
ans = 0
for i in xrange((N // M)^2 // 2):
    u = 2 * i + 1
    cur = calc(sqrt(u + 1 - eps)) - calc(sqrt(u - eps))
    ans += cur
    if i % 100 == 0:
        print [u, u + 1], cur
print ans