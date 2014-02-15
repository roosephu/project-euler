n = 10^7 - 10
m = 10^9

GF = Integers(5)
F = dict()

def dfs(dep, mod, lmt) :
    if dep == -1 :
        return lmt == 0 and mod == 0
    state = (dep, mod, lmt)
    if state in F :
        return F[state]

    F[state] = 0
    if ((n >> dep) & 1) == 0 :  # can be 0
        F[state] += dfs(dep - 1, mod, lmt if ((m >> dep) & 1) == 0 else 0)
    if lmt == 0 or ((m >> dep) & 1) == 1 :  # can be 1
        F[state] += dfs(dep - 1, mod + GF(2)^dep, lmt)
    return F[state]

ans = 0
dfs(64, GF(0), 1)
print bin(m), bin(n)
print m - n - ans
print sorted(list(F.items()))
