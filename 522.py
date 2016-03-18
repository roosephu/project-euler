def fac(n):
    if n == 0:
        return 1
    return fac(n - 1) * n

def cb(n, m):
    return fac(n) / fac(n - m) / fac(m)

n = 100

ans = 0
for i in range(1, n):
    ans += max(i - 1, 0) * cb(n - 1, i) * (n - 2)**(n - 1 - i) * (n - 1) * n
for i in range(2, n - 1):
    ans += cb(n, i) * fac(i - 1) * (n - i - 1)**(n - i)

print ans % 135707531
