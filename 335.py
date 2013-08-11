def calc(n) :
    f = [1] * n
    cnt = 0
    x = 0
    # print(f)
    while cnt == 0 or min(f) != 1 :
        y = f[x]
        f[x] = 0
        for i in range(y) :
            f[(x + 1 + i) % n] += 1
        x = (x + y) % n
        cnt += 1
        # print(f)
    return cnt

# for i in range(1, 101) :
#     print(i, calc(i))
# for i in range(10) :
#     print(i, 2**i + 1, calc(2**i + 1))
f = [2, 5, 15, 53, 207, 845, 3495, 14453, 59487, 243485]
# for i in range(3, len(f)) :
#     print(2 ** i + 1, f[i], f[i - 1] * 9 - f[i - 2] * 26 + f[i - 3] * 24)
# for i in range(len(f)) :
#     print(f[i], 2 * 2**i - 3**i + 4**i)

MOD = 7**9

def inv(x) :
    return pow(x, MOD - MOD // 7 - 1, MOD)

n = 10**18
ans = 2 * (pow(2, n + 1, MOD) - 1) * inv(2 - 1) - (pow(3, n + 1, MOD) - 1) * inv(3 - 1) + (pow(4, n + 1, MOD) - 1) * inv(4 - 1)
print((ans % MOD + MOD) % MOD)
