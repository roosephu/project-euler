from fractions import *

Qx, Qy = Fraction(7), Fraction(1)
Px1, Py1 = Fraction(13), Fraction(61, 4)
Px2, Py2 = Fraction(-43, 6), Fraction(-4, 1)

def M(x1, y1, x2, y2):
    return 12 * x1 * x2 + Fraction(7, 2) * (x1 * y2 + x2 * y1) - 12 * y1 * y2

MOD = int(1e9) + 7

last = 1
for i in range(10):
    Dx, Dy = Px1 - Qx, Py1 - Qy
    mu = M(Dx, Dy, Px2, Py2) / M(Dx, Dy, Qx, Qy) # (625 - M(Px1, Py1, Qx, Qy))
    Px3, Py3 = Px2 + mu * Dx, Py2 + mu * Dy

    print (Px3.numerator + Px3.denominator + Py3.numerator + Py3.denominator) % MOD, Px3, Py3
    cur = gcd(Px3.denominator, Py3.denominator)
    # print cur / last, last
    last = cur

    Px1, Py1 = Px2, Py2
    Px2, Py2 = Px3, Py3
