import numpy as np
from numba import jit

S = [1, 2, 3, 4, 5, 6, 8, 9, 10, 12, 15, 16, 18, 20, 24, 25, 27, 30]
S += [13, 26]
S += [11, 22]
S += [7, 14, 21, 28]
# S = range(1, 31)

# @jit
def compute(n, S):
    xs = set([1])
    lens = [1]
    for i in range(n):
        ys = set()
        for x in xs:
            for a in S:
                ys.add(a * x)
        xs = ys
        lens.append(len(xs))
        print(len(xs))
    return lens

lens = np.array(compute(8, S))
# lens = np.array([1, 30, 308, 1909, 8679, 31856, 99814, 276705, 695552, 1613612, 3500640])
coefs = []
degree = 8

for i in range(degree):
    coefs.append(int(lens[0]))
    print(lens)
    lens = lens[1:] - lens[:-1]

def interpolate(n):
    comb = 1
    ans = 0
    for i in range(degree):
        ans += coefs[i] * comb
        comb = comb * (n - i) // (i + 1)
    return ans

def C(a, b):
    ret = 1
    for i in range(b):
        ret = ret * (a - i) // (i + 1)
    return ret

n = 10001
ans = 0
for t in range(n + 1):
    ans += C(t + 3, 3) * interpolate(n - t)
MOD = 1000000007
print(ans, ans % MOD)
