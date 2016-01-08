from fractions import *

F = {}
ans = 0
def dfs(b, L, R, s):
    if L > R:
        if b:
            if s in F:
                F[s] += 1
            else:
                F[s] = 1
        else:
            s = Fraction(1, 2) - s
            if s in F:
                ans += F[s]
        return

    dfs(b, L + 1, R, s                     )
    dfs(b, L + 1, R, s + Fraction(1, L * L))

n = 45
dfs(True , 2, n // 2, Fraction(0))
dfs(False, n // 2 + 1, n, Fraction(0))
print ans
