ans = 0
for a in [1 .. 100] :
    for b in [(2 * a + 1) .. 100] :
        for d in [(2 * a + 1) .. 100] :
            if b + d >= 100 :
                break
            if 2 * a * a == (b - 2 * a) * (d - 2 * a) :
                print a, b, d
                ans += 1
print ans
