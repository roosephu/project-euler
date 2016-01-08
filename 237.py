G = {
    '1200': ['1002', '1212'],
    '0120': ['1002'],
    '0012': ['1002', '1212'],
    '1002': ['1200', '0120', '0012', '1122'],
    '1122': ['1122', '0012', '1200'],
    '1212': ['1212', '1002'],
}

m, MOD, n = 6, 10**8, 10**12 - 1
vertices = {x: y for y, x in enumerate(G.keys())}

U = [[0] * m for i in range(m)]
for v, us in G.items():
    for u in us:
        U[vertices[v]][vertices[u]] += 1

def matmul(a, b):
    c = [[0] * m for i in range(m)]
    for i in range(m):
        for j in range(m):
            for k in range(m):
                c[i][k] += a[i][j] * b[j][k]
                c[i][k] %= MOD
    return c

V = [[0] * m for i in range(m)]
V[0][vertices['1002']] = 1

while n > 0:
    if n % 2 == 1:
        V = matmul(V, U)
    U = matmul(U, U)
    n = n // 2
# for i in range(n):
#     V = matmul(V, U)
#     print V

ans = 0
for end in ['1002', '1122']:
    ans += V[0][vertices[end]]
print ans % MOD
