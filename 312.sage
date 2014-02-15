# R = Integers(13^8)
# a = R(2)
# f = {}
def bf(n) :
    a = Integers(13^8)(2)
    for i in [1 .. n - 3] :
        a = a^3 * 3
    return a^3

n = 10^4
mod = 13^6
# calc C(n) % 12*13^6
R = Integers(mod)
y = 1 / R(3).sqrt()
x = R(3).sqrt() * 2
# C(n) % 13^6 = x^(3^(n-3)) * y
ans = CRT(0, Integer(x^(pow(3, n - 2, 12 * 13^5)) * y^3), 12, mod)
print ans, bf(n)
assert R(ans) == R(bf(n))

# calc C(C(n)) % 12*13^7
mod = 13^7
R = Integers(mod)
y = 1 / R(3).sqrt()
x = R(3).sqrt() * 2
# C(n) % 13^6 = x^(3^(n-3)) * y
ans = CRT(0, Integer(x^(pow(3, Integer(ans) - 2, 12 * 13^6)) * y^3), 12, mod)

# calc C(C(C(n))) % 13^8
mod = 13^8
R = Integers(mod)
y = 1 / R(3).sqrt()
x = R(3).sqrt() * 2
# C(n) % 13^6 = x^(3^(n-3)) * y
ans = x^(pow(3, ans - 2, 12 * 13^7)) * y^3
print ans
