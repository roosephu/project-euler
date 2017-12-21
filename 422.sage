P = matrix([[7 / 50, 1 / 50], [1 / 50, -7 / 50]])
D = matrix([[1, 0], [0, -1]])
print "P^-1 = %s" % P.inverse()

Q = P * vector([7, 1])
print "Q = %s" % Q
P1 = P * vector([13, 61 / 4])
P2 = P * vector([-43 / 6, -4 / 1])
print P1
print P2

def M(p1, p2):
    return p1 * D * p2

MOD = int(1e9) + 7

last = 1
for i in range(3, 14):
    d = P1 - Q
    mu = M(d, P2) / M(d, Q)
    P3 = P2 + mu * d

#     print P.inverse() * P3
#     print P3, P1[0] * P2[0] - P1[1] * P2[1], P1[1] * P2[0] - P1[0] * P2[1]
    print P.inverse() * P3
    a, b = fibonacci(i - 2), fibonacci(i - 1)
    if i % 2 == 0:
        pass
#         print a, b, "(%d/%d, %d/%d)" % (2^(4 * a + 2 * b + 2) - (-3)^(2 * b + 1), (-3)^b * 2^(2 * a + b), 2^(4 * a + 2 * b - 2) + (-3)^(2 * b - 1), (-3)^(b-1) * 2^(2 * a + b - 2))
    else:
        print a, b, "(%d/%d, %d/%d)" % (2^(4 * a + 2 * b - 2) - (-3)^(2 * b - 1), -(-3)^(b-1) * 2^(2 * a + b - 2), 2^(4 * a + 2 * b + 2) + (-3)^(2 * b + 1), (-3)^b * 2^(2 * a + b))

    last = cur

    P1 = P2
    P2 = P3


n = 11^14

MOD = 10^9 + 7
Rx = Integers(MOD - 1)
Fp = Integers(MOD)
U = matrix(Rx, [[1, 1], [1, 0]])
x = vector(Rx, [1, 0])
fib_p = lambda n: (U^(n-1) * x)[0]
a, b = fib_p(n - 2), fib_p(n - 1)
print a, b

print sum([Fp(2)^(4 * a + 2 * b - 2) - Fp(-3)^(2 * b - 1),
           -Fp(-3)^(b-1) * Fp(2)^(2 * a + b - 2),
           Fp(2)^(4 * a + 2 * b + 2) + Fp(-3)^(2 * b + 1),
           Fp(-3)^b * Fp(2)^(2 * a + b)])
