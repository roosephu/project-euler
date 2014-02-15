from gc import collect

ans = 2255375755669783454
lmt = 9470107
lx = 0
for p in primes(10^7) :
    if p <= lmt :
        continue
    x = p * p
    if legendre_symbol(13, p) == 1 :
        y1 = Integers(x)(13).sqrt()
        y2 = x - y1
        cur = min((3 + y1) / 2, (3 - y1) / 2, (3 + y2) / 2, (3 - y2) / 2)
        ans += int(cur)
        if p // 10000 != lx :
            lx = p // 10000
            print p, cur, ans
print ans
