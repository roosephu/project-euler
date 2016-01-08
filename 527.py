from math import *

# S = 0.
# H = 0.
# for i in range(1, 7):
#     S = S * (i + 2) / i + i
#     H += 1. / (i + 1)
#     print 'f[%d] = %f, H = %f, g(H) = %f' % (i, S, H, (i + 2) * (i + 1) * (H - i / (i + 2.)))

def H(n):
    if n < 1e6:
        ret = 0
        for i in range(n):
            ret += 1. / (i + 1)
    else:
        gamma = 0.57721566490153286060
        ret = log(n) + gamma + 1. / 2 / n - 1. / 12 / n / n + 1. / 120 / n / n / n / n
    return ret

def R(n):
    return 2 * H(n) * (n + 1) / n - 3

def B(n, T={0: 0.}):
    if n not in T:
        L = n // 2
        R = n - 1 - L
        T[n] = B(L) * L / n + B(R) * R / n + 1
    return T[n]

n = 10**10
print R(n) - B(n)
