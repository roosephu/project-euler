from collections import defaultdict

f = defaultdict(int)

def can_make(x, a, b): # x = a * p + b * q
    # print x, a, b
    p = gcd(a, b)
    a //= p
    b //= p

    if x % p != 0:
        return False
    x //= p

    if a % b == 0:
        return x % b == 0
    if b % a == 0:
        return x % a == 0

    # print type(a), type(b)
    # print x, a, b, inverse_mod(b, a)
    q = inverse_mod(b, a) * x % a
    p = inverse_mod(a, b) * x % b
    return (a * p + b * q) <= x

def can(n, m):
    if is_odd(n):
        if is_odd(m):
            return False
        if n == 1:
            return True
        return can_make(m, n - 1, n + 1)
    else:
        return can_make(m, n - 1, n + 1) or can_make(m - 1, n - 1, n + 1) or can_make(m + 1, n - 1, n + 1)
    return False

lmt = 200000
for n in range(1, lmt + 1):
    for m in range(1, lmt // n + 1):
        if m > n:
            break
        if not can(n, m) and not can(m, n) and is_even(n * m):
            f[n * m] += 1
            # print n, m, can(m, n), can(n, m)

for a, b in sorted(f.items()):
    if b >= 20:
        print 'bad', a, b
