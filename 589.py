import numpy as np
import numba as nb

@nb.jit(nb.float64(nb.int32, nb.int32))
def solve(L, R):
    A = np.zeros((R + 6, R + 6), dtype=np.float64)
    v = np.zeros(R + 6, dtype=np.float64)
    for x in range(R + 6):
        A[x, x] = (R - L + 1) * (R - L + 1)
        v[x] = 5 * (R - L + 1) * (R - L + 1)

        Lp = max(x - 5, L)
        v[x] += (R - L + 1) * (Lp - L) * (L + Lp - 1) / 2.

        for a in range(Lp, R + 1):
            for b in range(L + x, R + x + 1):
                if a <= b:
                    v[x] += a
                    A[x, b - a] -= 1.
                else:
                    v[x] += b
                    A[x, a - b] -= 1.
    f = np.linalg.solve(A, v)
    return f[0] - 5

import time
ans = 0
K = 100
t0 = time.time()
# for i in range(10):
#     solve(1, 100)
# print(time.time() - t0)
for L in range(1, K):
    print(L, time.time() - t0)
    for R in range(L, K):
        ans += solve(L, R + 1)
print("%.6f" % ans)
