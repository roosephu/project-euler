
def cb(n, m):
    return factorial(n) / factorial(m) / factorial(n - m)

def f(a, b):
    n = a + b
    s = 0
    for i in range(a):
        s += cb(n - 1, i)
    return s / 2**(n - 1) * n

# for i in range(6):
#     print f(i, 5 - i)
#     s = 0
#     if i > 0 and i < 5:
#         s += f(i + 1, 4 - i) * i / 5
#         s += f(i - 1, 6 - i) * (5 - i) / 5
#     print s

# n = 5
# for i in range(n + 1):
#     print "%d: %.5f" % (i, f(n, i))

# for i in range(10):
#     print "%.6f %.6f %.6f" % (f(i, i + 2), f(i, i + 1), f(i, i))

def g(a, b, p):
    if a < b:
        return g(a, a, p)
    if b == 0:
        return a * p
    if a == 0:
        return 0
    if p < 1e-8:
        return f(a, b) * p
    p1 = a / (a + b)
    p2 = b / (a + b)
    return g(a + 1, b - 1, p * p1) + g(a - 1, b + 1, p * p2)

print g(5, 5, 1.)
