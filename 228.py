# L, R = 1864, 1909 + 1
L, R = 3, 4 + 1

def gcd(a, b):
    while a:
        a, b = b % a, a
    return b

F = []
for i in range(L, R):
    for j in range(i):
        g = gcd(i, j)
        F += [(i // g, j // g)]

print 'ans = %d' % (len(set(F)))
