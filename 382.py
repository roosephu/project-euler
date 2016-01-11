f = [0] * 100
g = [0] * 100

ans = 0
for i in range(4, 30):
    g[i] = 2**max(i - 5, 0) - 1 + f[i - 4] + g[i - 3]
    f[i] = g[i] + 2**(i - 3) + 2**(i - 4) - 1 + f[i - 3]
    ans += f[i]
    print i, ans
