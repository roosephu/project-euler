from collections import defaultdict

f = {(0, 0, 0, 0, 0): 1}

for _ in range(70):
    g = defaultdict(int)

    print _, len(f)
    for key, val in f.items():
        L, R = list(key), list(key)
        # print L, R, R[len(R) - 1], R[:-1]
        L = L[1:] + [-L[0]]
        L[0] += 1

        R = [-R[-1]] + R[:-1]
        R[0] += 1

        g[tuple(L)] += 1
        g[tuple(R)] += 1
    f = g
