for n in range(2, 10000):
    if n % 100 == 1:
        print n
    b = True
    for divisor in prime_divisors(n):
        if divisor not in [2, 3, 5, 7, 17, 257]:
            b = False
            break
    if not b:
        continue
    for m in range(1, n // 2):
        if gcd(n, m) == 1:
            cf = continued_fraction(cos(m * pi / n))
            if cf[19] != 0:
                continue
            print n, m, cf
