︠5975998a-dd9d-4d61-bda4-5974b654a7c5s︠
n = 13082761331670030
dvs = list(factor(n))
print dvs
f = []

for p, _ in dvs:
    L = []
    for i in range(p):
        if i**3 % p == 1:
            L += [i]
    f += [(p, L)]

ans = 0

def dfs(dep, rem, ps):
    if dep == len(f):
        global ans

        cur = crt(rem, ps)
        if cur != 1:
            ans += cur
        return 

    p, L = f[dep]
    for i in L:
        dfs(dep + 1, rem + [i], ps + [p])

dfs(0, [], [])
print ans
︡496816b0-5f2d-454c-958c-52c3c30c5851︡︡{"stdout":"[(2, 1), (3, 1), (5, 1), (7, 1), (11, 1), (13, 1), (17, 1), (19, 1), (23, 1), (29, 1), (31, 1), (37, 1), (41, 1), (43, 1)]\n","done":false}︡{"stdout":"4617456485273129588\n","done":false}︡{"done":true}
︠2609fbd5-21aa-4508-b571-3e42e43d69ba︠









