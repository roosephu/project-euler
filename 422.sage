
Qx, Qy = 7, 1
Px1, Py1 = 13, 61 / 4
Px2, Py2 = -43 / 6, -4 / 1

def M(x1, y1, x2, y2):
    return 24 * x1 * x2 + 7 * (x1 * y2 + x2 * y1) - 24 * y1 * y2

MOD = int(1e9) + 7

last = 1
for i in range(10):
    Dx, Dy = Px1 - Qx, Py1 - Qy
    mu = M(Dx, Dy, Px2, Py2) / M(Dx, Dy, Qx, Qy) # (625 - M(Px1, Py1, Qx, Qy))
    Px3, Py3 = Px2 + mu * Dx, Py2 + mu * Dy

    print (Px3.numerator + Px3.denominator + Py3.numerator + Py3.denominator) % MOD, Px3 - Qx, Py3 - Qy
    cur = gcd(Px3.denominator, Py3.denominator)
    # print cur / last, last
    last = cur

    Px1, Py1 = Px2, Py2
    Px2, Py2 = Px3, Py3
