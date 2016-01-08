n = 20

f = [[0] * (n * 81 + 1) for i in range(n + 1)]
g = [[0] * (n * 81 + 1) for i in range(n + 1)]

f[0][0], g[0][0] = 1, 0 # cnt, sum

for i in range(n):
    for j in range(i * 81 + 1):
        for k in range(10):
            f[i + 1][j + k * k] += f[i][j]
            g[i + 1][j + k * k] += g[i][j] + k * 10**i * f[i][j]

ans = 0
for i in range(n * 9):
    if i * i > n * 9 * 9:
        break
    ans += g[n][i * i]
print ans
