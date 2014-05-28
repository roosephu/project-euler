
ans = 0
for a in range(1, 100) :
    for k in range(1, 10) :
        for d in range(1, 10) :
            if d * (10**a - k) % (10 * k - 1) == 0 :
                s = d * (10**a - k) / (10 * k - 1)
                if 10**(a - 1) <= s and s < 10**a :
                    ans += 10 * s + d
                    print(10 * s + d)
print(ans)
