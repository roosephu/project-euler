t = var('t')
m = 15
f = e^(t * m)
for i in range(50):
    f -= e^(2^i * t) / 2^(i + 1)
f_d = f.derivative()
t0 = -2e-9
for i in range(10):
    print t0, f(t=t0).n(100)
    t0 = (t0 - f(t=t0) / f_d(t=t0)).n(100)
# plot(f, (t, -3e-9, 0))
print(1 - e^(t0*1e9))
