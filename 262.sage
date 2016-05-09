import numpy as np

# figure()
x, y = var('x, y')
h = 1000 * (5 - 5 / 1000000 * (x * x + y * y + x * y) + 125 / 10000 * (x + y)) * exp(-abs(1 / 1000000 * (x * x + y * y) - 15 / 10000 * (x + y) + 7 / 10))

f_min, x_left = find_local_maximum(h(y=0), 0, 1600)
h_p = h(x=x, y=x)
print h_p
x_start = find_root(h_p - f_min, 0, 800)
x_end = find_root(h_p - f_min, 800, 1600)

ans = 0
ans += f_min - h(200, 200) + (x_start - 200) * sqrt(2)
ans += f_min - h(1400, 1400) + (1400 - x_end) * sqrt(2)

print 'ans = %.3f' % (ans)

# plot3d(h, (x, 0, 1600), (y, 0, 1600), adaptive=True).show()

f_2d = h(x, y) - f_min
dx, dy = f.derivative(x), f.derivative(y)

def f1(x):
    y = find_root(f_2d(y=x), 0, x_left)
    print x, y, f_2d(x=x, y=0), f_2d(x=x, y=x_left)
    return sqrt(1 + (dy(x=x, y=y) / dx(x=x, y=y))**2)

print numerical_integral(f1, 0, x_start, eps_abs=1e-4)

# fn = sqrt(dx * dx + dy * dy)
# ff = (dx / fn).derivative(x) + (dy / fn).derivative(y)
# # print ff
# print ff.full_simplify()
