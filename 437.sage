
ans = 0
lx = 0
for p in primes(10^8) :
    if kronecker(5, p) == -1 :
        continue
    if p > lx :
        print p
        lx += 10^5
    R = Integers(p)
    m, d = R(-1) / 2, R(5).sqrt() / 2
    x, y = m + d, m - d
    if multiplicative_order(x) == p - 1 or multiplicative_order(y) == p - 1 :
        ans += p
        # print p
print ans
