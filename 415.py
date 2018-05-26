from math import gcd

F = [[{} for a in range(2)] for b in range(2)]

def partial_sum(n, k):
    if k == 0:
        return n
    if k == 1:
        return n * (n + 1) // 2
    if k == 2:
        return n * (n + 1) * (n * 2 + 1) // 6
    assert 0

def dfs(n, a, b): #
    global F

    if n not in F[a][b]:
        S = partial_sum(n, a) * partial_sum(n, b)
        i = 2
        last_coef = partial_sum(1, a + b)
        while i <= n:
            j = n // (n // i) + 1
            coef = partial_sum(j - 1, a + b)
            S -= (coef - last_coef) * dfs(n // i, a, b)

            last_coef = coef
            i = j
        F[a][b][n] = S

    return F[a][b][n]

def solve(n):
    ans = 0
    for g in range(1, n):
        S00, S01, S10, S11 = dfs(n // g, 0, 0), dfs(n // g, 0, 1), dfs(n // g, 1, 0), dfs(n // g, 1, 1)
        print(g, S00, S01, S10, S11)
        ans += 2**g * (S00 * n * n - (S01 + S10) * n * g + S11 * g * g)
    return ans

def solve_bf(n):
    ans = 0
    for x in range(1, n):
        for y in range(1, n):
            ans += 2**gcd(x, y) * (n - x) * (n - y)
    return ans

print(solve(5))
print(solve_bf(5))
