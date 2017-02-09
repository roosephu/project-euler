a, b, x = var('a, b, x')
f, g = x^3 + b, (x + a)^3 + b
f, g = f, g - f
f, g = x * g - 3 * a * f, g
f, g = g * a - f, g
f, g = f, g * 2 * a^2 - f * 3 * x
f, g = f, g * 2 * a^3 - f * (3 * a^4 - 9 * a * b)
print expand(f), "|", expand(g)

# ===========

def calc(a, b, g): # maximize a x + b == 0 mod g
    t = gcd(a, g)
    if b % t != 0:
        return []
    a, b, g = a // t, b // t, g // t
#     print a, b, g
#     print inverse_mod(a, g)
    seed = (g - b) * inverse_mod(a, g) % g
    ret = []
    for i in range(t):
        ret += [seed]
        seed += g
    return ret

def bf(a, b):
    ret = 0
    for x in range(100000):
        t = gcd(x^3 + b, (x + a)^3 + b)
        if t > ret:
            print x
            ret = t
    return ret

def solve(a, b):
    G = a^8 + 27 * a^2 * b^2
    A, B = 2 * a^3, 3 * a * b + a^4
    val, ret = 0, 0
    for g in reversed(divisors(G)):
        for x in calc(A, B, g):
            t = gcd(x^3 + b, (x + a)^3 + b)
            if t > val:
                val, ret = t, x
            elif t == val and x < ret:
                ret = x
            if ret >= g:
                break
        if ret >= g:
            break
#     print 'a = %d, b = %d, val = %d, ret = %d, G = %d' % (a, b, val, ret, G)
    return ret

ans = 0
for a in range(1, 18 + 1):
    print a
    for b in range(1, 1900 + 1):
        ret = solve(a, b)
        ans += ret
print 'ans = %d' % (ans,)
# print solve(2, 4, 28)

#


