import numpy as np
from numba import jit

partitions = []
n = 20
MOD = np.int64(1001001011)

factorial = np.zeros(n + 1, dtype=np.int64)
factorial[0] = 1
last = 1
for i in range(1, n + 1):
    last = last * i % MOD
    factorial[i] = last

@jit('i8(i8, i8, i8)')
def power(b, e, m):
    t = 1
    while e > 0:
        if e & 1:
            t = t * b % m
        b = b * b % m
        e = e >> 1
    return t

@jit('i8(i8)')
def inv(x):
    return power(x, MOD - 2, MOD)

def dfs(p, rem, last):
    if rem == 0:
        total = factorial[n]
        cnt = [0] * (n + 1)
        for a in p:
            cnt[a] += 1
        for i in range(n + 1):
            total = total * inv(factorial[cnt[i]]) % MOD * inv(power(i, cnt[i], MOD)) % MOD
        # print(p, total, factorial[n])
        partitions.append([np.array(p), total])
        return
    last = min(rem, last)
    for i in range(last, 0, -1):
        dfs(p + [i], rem - i, i)

dfs([], n, n)
print(sum([b for a, b in partitions]))
# print(partitions)

@jit('u8(u8,u8)')
def gcd(a, b):
    return b if a == 0 else gcd(b % a, a)

@jit("i8(i8[:], i8[:])")
def countf(pa, pb):
    # print(pa.size, pb.size)
    m = pa.size + pb.size
    x = np.zeros(m, dtype=np.int64)
    n_sols = n * 2
    freedom = 0
    for i, A in enumerate(pa):
        for j, B in enumerate(pb):
            g = gcd(A, B)
            a, b = A // g, B // g
            freedom += g
            y = 0
            if b % 2 == 1:
                y |= 1 << i
            if a % 2 == 1:
                y |= 1 << (j + pa.size)
            # print(bin(y))

            for t in range(m):
                if y >> t & 1:
                    if x[t] == 0:
                        x[t] = y
                        break
                    else:
                        y ^= x[t]

    for t in range(m):
        if x[t] != 0:
            n_sols -= 1
    # print(pa, pb, freedom, n_sols)
    # return 2**(freedom + n_sols - n * 2)
    return power(2, freedom + n_sols - n * 2, MOD)

# countf.inspect_types()
print(len(partitions))

# countf(np.array([1, 1, 1, 1, 1]), np.array([1, 1, 1, 1, 1]))
ans = 0

import time

ta = time.perf_counter()
for a, cntA in partitions:
    for b, cntB in partitions:
        ans += countf(a, b) * cntA % MOD * cntB % MOD
tb = time.perf_counter()
print(ans % MOD * (inv(factorial[n])**2 % MOD) % MOD)
print(tb - ta)
