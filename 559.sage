k, r, n = 1, 2, 3
# k, r, n = 2, 4, 6
ans = 0
t = (n - 1) // k
for i in range(t + 1):
    ans += factorial(t) // factorial(i) // factorial(t - i) * (-1)**i * (factorial(n) // (n - t + i))**r

print ans
