import numpy as np
from numba import jit

@jit("i8(i8)")
def solve(N):
    MOD = 10**9 + 7
    MAX_SYMBOL = N // 5
    f = np.zeros((MAX_SYMBOL + 1, N + 1), dtype=np.int64)
    for t in range(MAX_SYMBOL, -1, -1):
#         print(t)
        for n in range(1, N + 1):
            if n == 1:
                f[t, n] = t
            else:
                if t < MAX_SYMBOL and n >= 5:
                    f[t, n] += f[t + 1, n - 5]
                for a in range(1, n - 2):
                    b = n - 2 - a
                    f[t, n] += f[t, a] * f[t, b] % MOD
                f[t, n] %= MOD
#     print(f[0])
    ans = np.sum(f[0])
    return ans % MOD

solve.recompile()
print(solve(2000))
