n = 15
with open("345.in", "r") as fin :
    G = []
    for i in [1 .. n] :
        G += [map(int, fin.readline().split(' ')[:n])]

f = [0] * (1 << n)
for S in [0 .. (1 << n) - 1] :
    x = 0
    for i in [0 .. (n - 1)] :
        if (S >> i) & 1 :
            x += 1
    for y in [0 .. (n - 1)] :
        if not ((S >> y) & 1) :
            f[S | 1 << y] = max(f[S | 1 << y], f[S] + G[x][y])
print f[(1 << n) - 1]
