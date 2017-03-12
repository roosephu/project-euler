# Block 1
import numpy as np
from math import hypot

# figure()
x, y = var('x, y')
h = 1000 * (5 - 5 / 1000000 * (x * x + y * y + x * y) + 125 / 10000 * (x + y)) * exp(-abs(1 / 1000000 * (x * x + y * y) - 15 / 10000 * (x + y) + 7 / 10))

f_min, x_left = find_local_maximum(h(y=0), 0, 1600)

print u - f_v(u=u) / f_v.derivative()(u=u)
u_l =  200 * sqrt(2.)
u_r = 1400 * sqrt(2.)
x_L = find_root(lambda x: (u - f_v / f_v.derivative() - u_l)(u=x),  387.,  900.)
x_R = find_root(lambda x: (u - f_v / f_v.derivative() - u_r)(u=x), 1200., 1828.)
print x_L, x_R

# print (x_end - x_start) * sqrt(2).n() / 2 * pi.n()

ans = hypot(u_l - x_L, f_v(u=x_L)) + hypot(u_r - x_R, f_v(u=x_R))
ans += 1536.0161445693104

print 'ans = %.3f' % (ans)

# Block 2
f_v = sqrt(A - lambert_w(height / 2500. * exp(A - B))) * 1000.
L = find_root(h3(v=0) == height, 0, 1000)
R = find_root(h3(v=0) == height, 1000, 2000)
print "L = %.3f, R = %.3f" % (L, R)

p_x = ((500 + f_v(u=500)) / sqrt(2)).n()
p_y = ((500 - f_v(u=500)) / sqrt(2)).n()
print p_x, p_y, h3(u=500, v=f_v(u=500)).n()

int_f = sqrt(f_v.derivative()^2 + 1)
def F(u):
    print u
    return int_f(u=u).n()

# print F(L + 1e-9), F(R)
numerical_integral(F, x_L, x_R, eps_abs=1e-9, eps_rel=1e-9, algorithm='qags')
# plot(f_v, 0.5, 1)
# scatter_plot([(i, f_v(u=i).n(100)) for i in np.linspace(0.5, 1, 1000)])

# Block 3
u, v = var('u, v')
A = 2. - 3. * u^2 / 10.^6 + sqrt(2.) * u / 200.
B = -u^2 / 10^6. + 3. * sqrt(2.) * u / 2000. - 0.7
h3 = (A - v^2 / 10.^6) * exp(B - v^2 / 10.^6) * 2500.
implicit_plot(h3 == height, (u, 0, 2000), (v, -1000, 1000)) + scatter_plot([(x_start * sqrt(2), 0), (x_end * sqrt(2), 0)])