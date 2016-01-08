def P(f, r):
    first, start = f * f // 2, f // 2 * 2 + 1
    if f == 1:
        r += 1
    if r % 2 == 0:
        first = start * start - first
        start += 1
        r -= 1
    return first + (start + start + r - 2) * (r - 1) // 2

print P(99, 100), P(1, 1), P(1, 2), P(2, 1), P(25, 75), P(10, 20)

ans = 0
n = 71328803586048
for i in range(1, 10000000):
    if n % i == 0:
        print i
        ans += P(i, n // i)
        ans += P(n // i, i)
    if i * i > n:
        break
print 'ans', ans
