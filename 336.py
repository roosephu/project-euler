import string
Q = [[2, 1]]

for n in range(3, 11 + 1):
    print n
    P = []
    for seq in Q:
        t = list(reversed([1] + [x + 1 for x in seq]))
        for y in range(1, n - 1):
            P += [t[:y] + list(reversed(t[y:]))]
    Q = P

Q = sorted(Q)
print "".join([string.uppercase[x - 1] for x in Q[2011 - 1]])
