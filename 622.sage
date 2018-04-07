x = 60
F = {}
for t in divisors(x):
    x = 2**t - 1
    ans = 0
    for d in divisors(x):
        ans += d + 1
    for tt in divisors(t):
        if tt != t:
            ans -= F[tt]
    F[t] = ans
