D = 5. * sqrt(2.)
d = 1
dd = D - d * 5
vs = [0.9, 0.8, 0.7, 0.6, 0.5]

def f(x):
    global D, d, dd, vs
    ret = 0
    for v in vs:
        ret += 1 / sqrt((1. + 1. / x / x) / v / v - 1)
    return ret * d + dd * x - D

def g(x):
    sin_theta0 = 1 / sqrt(1 / x / x + 1)
    cos_theta0 = sqrt(1 - sin_theta0^2)
    ret = dd / cos_theta0
    for v in vs:
        sin_thetai = sin_theta0 * v
        cos_thetai = sqrt(1 - sin_thetai^2)
        ret += d / cos_thetai / v
    return ret

x = var('x')

val_x = find_root(f(x), 0, 2)
print g(val_x), f(val_x), val_x