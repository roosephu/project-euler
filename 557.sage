ans = 0
n = 20
for a in range(1, n + 1):
    for b in range(1, n + 1):
        for c in range(b, n + 1):
            for d in range(1, n + 1):
                S = a + b + c + d
                if b * c * (S + a) == a * a * d and S <= n:
                    print a, b, c, d
                    ans += S
print ans
