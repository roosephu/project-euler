n = 10**18 + 1

def count(n): # sum_{0<=i<n} sum_{0<=j<n} i + j + (i ^ j)
    ret = 0
    for i in reversed(range(64)):
        rep = n // 2**(i + 1)
        rem = n % 2**(i + 1)
        zeros = rep * 2**i + min(2**i, rem)
        ones = n - zeros
        ret += zeros * ones * 2**i
    return ret * 2 + n * n * (n - 1)

ans = -3 * n * (n - 1)
baseline = 0
for i in reversed(range(64)):
    if n >> i & 1:
        k = 1 << i
        ans += count(k)
        ans += 3 * (count(n - k) + (n - k) * (n - k) * k * 2)
        ans -= 3 * (k * k + 3 * (n - k) * (n - k) - (3 * n - 2))
        # ans += baseline * (k * k + 2 * (n - k) * (n - k) ) * 2
        break
assert ans % 6 == 0
ans = ans / 6
if n % 2 == 0:
    ans -= (n - 2) * (n - 1) / 2
else:
    ans -= (n - 2) * (n - 3) / 2
print ans
exit()

ans = 0
for i in range(2, n):
    for j in range(i + 1, n):
        if j < i ^ j < n:
            # print i - 1, j - 1, (i ^ j) - 1
            ans += i + j + (i ^ j) - 3
print ans
