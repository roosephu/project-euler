tn = 10000
N = tn + 10
ans = 0
for _ in range(2, 3) :
    p = n(_ / 100, digits = 100)
    f = [0] * N
    g = [0] * N
    f[:2], g[:2] = [0, 1], [N, 0]
    P = [(1 - p)**i for i in range(N)]
    for i in range(2, N) :
        f[i] = g[i] = i
        for k in range(1, i) :
            t = (P[k] - P[i]) / (1 - P[i])
            g[i] = min(g[i], (1 - t) * (f[i - k] + g[k]) + t * g[i - k] + 1)
        for k in range(1, i + 1) :
            t = P[i]
            f[i] = min(f[i], f[i - k] + (1 - t) * g[k] + 1)
        if i % 100 == 0 :
            print i, f[i]
