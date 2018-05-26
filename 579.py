# See https://arxiv.org/pdf/1111.1150.pdf
from numba import jit
from math import sqrt
import numpy as np

def cmp(a, b):
    return a.tolist() < b.tolist()

T1 = []
T2 = []

# LMT = 39
# print('LMT = ', LMT)

def gcd(a):
    t = 0
    for x in a:
        while x != 0:
            x, t = t % x, x
    return abs(t)

def nLattice(a, b, c, t):
    # g = abs(gcd(np.r_[a, b, c]))
    # d_1 = gcd([a[0], b[0], c[0]]) // g
    # d_2 = gcd([a[1], b[1], c[1]]) // g
    # d_3 = gcd([a[2], b[2], c[2]]) // g
    assert a.dot(a) == t * t
    d_1, d_2, d_3 = abs(gcd(a)), abs(gcd(b)), abs(gcd(c))
    return (t + 1) * (t * t - t + 1 + d_1 + d_2 + d_3)

# @jit('i8()')
def test(n):
    ans = 0
    S = [[] for i in range(n + 1)]
    for i in range(-n, n + 1):
        for j in range(-n, n + 1):
            if i * i + j * j > n * n:
                continue
            for k in range(-n, n + 1):
                L = i * i + j * j + k * k
                if L > n * n:
                    continue
                t = int(sqrt(L))
                if t * t != L: continue
                S[t].append(np.array([i, j, k]))
    compl = 0
    for t, L in enumerate(S):
        norm = t
        if norm == 0: continue
        # compl += len(L)**2
        for a in L:
            if cmp(a, -a): continue
            # print(a)
            for b in L:
                if cmp(b, a): continue
                if a.dot(b) != 0: continue

                # done = False
                # if s1 * 2 == s:
                #     a1, done = -a1, True
                # elif s2 * 2 == s:
                #     a2, done = -a2, True
                # elif s3 * 2 == s:
                #     a3, done = -a3, True

                if True:
                # if done:
                    c = np.cross(a, b)
                    if np.any(c % norm): continue
                    if cmp(c, -c): c = -c
                    c = c // norm
                    if cmp(c, b): continue
                    if np.max(np.abs(c)) <= n:
                        x = np.abs(a) + np.abs(b) + np.abs(c)
                        if np.max(x) <= n:
                            # print(a, b, c)
                            g = gcd(x)
                            # if t != LMT or np.max(x) < n: continue
                            # print(a, b, c, t)

                            compl += np.product(n + 1 - x) * nLattice(a, b, c, t)
                            # T1.append((a.tolist(), b.tolist(), c.tolist(), t, nLattice(a, b, c, t)))
                            # compl += 1
    return compl

@jit('Tuple((i8, i8[:]))(i8)', nopython=True)
def gen(n):
    ans = 0
    stages = np.zeros(10, dtype=np.int64)
    MOD = 2 * 10**9

    def gcd(a):
        t = 0
        for x in a:
            while x != 0:
                x, t = t % x, x
        return abs(t)

    def nLattice(a, b, c, t):
        # g = abs(gcd(np.r_[a, b, c]))
        # d_1 = gcd([a[0], b[0], c[0]]) // g
        # d_2 = gcd([a[1], b[1], c[1]]) // g
        # d_3 = gcd([a[2], b[2], c[2]]) // g
        # assert a.dot(a) == b.dot(b) == c.dot(c) == t * t
        d_1, d_2, d_3 = abs(gcd(a)), abs(gcd(b)), abs(gcd(c))
        return (t + 1) * (t * t - t + 1 + d_1 + d_2 + d_3)

    def cmp(a, b):
        if a[0] != b[0]: return a[0] < b[0]
        if a[1] != b[1]: return a[1] < b[1]
        if a[2] != b[2]: return a[2] < b[2]
        return False

    def add(M, t):
        nonlocal ans
        stages[3] += 1

        # nonlocal num_trials
        if cmp(-M[0], M[0]) and cmp(M[0], M[1]) and cmp(M[1], M[2]):
            stages[4] += 1
        # if M[0, 0] <= M[1, 1] <= M[2, 2]:
        # if True:
        # if M[0, 0] <= 0 and M[0, 1] >= 0 and M[0, 2] >= 0:
            g = gcd(M.ravel())
            M = M // g
            t = t // g
            y = np.sum(np.abs(M), axis=0)
            max_scale = n // np.max(y)
            # if t != 43 and t != 1:
            #     # print(M[0], M[1], M[2], t)
            #     return
            # else:
                # max_scale = min(max_scale, 1)

            if max_scale > 0:
                stages[5] += 1
                # S.append((M[0].tolist(), M[1].tolist(), M[2].tolist()))
                for scale in range(1, max_scale + 1):
                    # if t * scale != LMT or scale * np.max(y) < n: continue
                    # print(M[0], M[1], M[2], g, ans)
                    ans += np.prod(n + 1 - y * scale) % MOD * (nLattice(M[0] * scale, M[1] * scale, M[2] * scale, t * scale) % MOD) % MOD
                    # T2.append(((M[0] * scale).tolist(), (M[1] * scale).tolist(), (M[2] * scale).tolist(), t * scale, nLattice(M[0] * scale, M[1] * scale, M[2] * scale, t * scale)))

    def SqrRoot(x):
        return int(sqrt(x + 0.9))

    def addTuple(case, a, b, c, d):
        stages[0] += 1
        if gcd([a, b, c, d]) != 1: return
        stages[1] += 1

        M0, M1, M2 = a**2 + b**2 - c**2 - d**2, 2 * (b * c + a * d), 2 * (b * d - c * a)
        M3, M4, M5 = 2 * (b * c - a * d), a**2 - b**2 + c**2 - d**2, 2 * (c * d + b * a)
        M6, M7, M8 = 2 * (b * d + c * a), 2 * (c * d - b * a), a**2 - b**2 - c**2 + d**2

        if not (0 <= M0 <= M3 <= M6 or 0 >= M0 >= M3 >= M6):
            return
        stages[2] += 1

        M = np.array([
            M0, M1, M2,
            M3, M4, M5,
            M6, M7, M8,
        ]).reshape((3, 3))
        t = a * a + b * b + c * c + d * d
        if t > 4 * n: return
        # if np.linalg.det(M) >= 0:
        if case == 0 and 0 <= M[0, 0] <= M[1, 0] <= M[2, 0]:
            add(M, t)
        if case == 1 and 0 >= M[0, 0] >= M[1, 0] >= M[2, 0]:
            add(-M, t)

    for case in range(2):
        for a in range(-n, n + 1):
            if a * a > 4 * n: continue
            print(a)
            for b in range(-n, n + 1):
                if a * a + b * b > 4 * n: continue
                # if gcd([a, b]) != 1: continue
                for c in range(-n, n + 1):
                    if a * a + b * b + c * c > 4 * n: continue
                    # if gcd([a, c]) != 1 or gcd([b, c]) != 1: continue

                    L, R = -SqrRoot(5 * n - a**2 - b**2 - c**2), SqrRoot(5 * n - a**2 - b**2 - c**2)
                    L, R = max(L, -n), min(R, n)
                    if (a + b > 0 and case == 0) or (a + b < 0 and case == 1):
                        L = max(L, (b - a) * c // (a + b) - 1)
                    elif (a + b > 0 and case == 1) or (a + b < 0 and case == 0):
                        R = min(R, (b - a) * c // (a + b) + 1)

                    t1, t2 = 2 * a**2 + b**2 - c**2 - 2 * b * c, a**2 + b**2 - c**2
                    if (case == 0 and t2 < 0) or (case == 1 and t1 < 0):
                        continue
                    t1, t2 = max(t1, 0), max(t2, 0)
                    if case == 0:
                        t = SqrRoot(t2) + 1
                        L, R = max(L, -t), min(R, +t)
                        Lj, Rj = a - SqrRoot(t1) + 1, a + SqrRoot(t1) - 1
                    else:
                        t = SqrRoot(t1) + 1
                        L, R = max(L, a - t) , min(R, a + t)
                        Lj, Rj = -SqrRoot(t2) + 1, +SqrRoot(t2) - 1
                    # for d in range(Lj, Rj + 1):
                    #     if case == 0:
                    #         assert a**2 + b**2 - c**2 - d**2 > 2 * (b * c - a * d)

                    if Rj < L or R < Lj or True:
                        for d in range(L, R + 1):
                            addTuple(case, a, b, c, d)
                    else:
                        bp = MOD
                        for d in range(L, R + 1):
                            if Lj <= d <= Rj:
                                break
                            bp = d
                            addTuple(case, a, b, c, d)
                        for d in range(R, L - 1, -1):
                            if Lj <= d <= Rj or d == bp:
                                break
                            addTuple(case, a, b, c, d)

    # print(f'stages = {stages}')
    # print('stages', stages)
    return ans // 2 % MOD, stages

# gen.inspect_types()
n = 5000
# test.inspect_types()
# print((test(n),))
print(gen(n))
# print(nLattice([1, 2, 2], [2, -2, 1], [2, 1, -2], 3))

# T1 = sorted(T1)
# T2 = sorted(T2)

# for a in zip(T1, T2):
#     print(a)
