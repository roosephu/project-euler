from fractions import *

class Frac(Fraction) :
    def __repr__(self) :
        return "%d/%d" % (self.numerator, self.denominator)

def delta(x0, y0, k) :
    return -(((24 + 7 * k) * x0 + (7 - 24 * k) * y0) / (12 + 7 * k - 12 * k * k))

X = (7, 1)
P = [(Frac(13), Frac(61, 4)), (Frac(-43, 6), Frac(-4, 1))]

for i in range(10) :
    x0, y0 = P[i + 1]
    x1, y1 = P[i]
    k = (y1 - X[1]) / (x1 - X[0])
    dx = delta(x0, y0, k)
    P += [(Frac(x0 + dx), Frac(y0 + dx * k))]

print(P)
