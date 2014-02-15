
f = [[[0] * (20 + 1) for i in [0 .. 70]] for j in [0 .. 12]]

def comb(n, m) :
    return factorial(n) / factorial(n - m) / factorial(m)

f[12][0][0] = 1
for i in range(12, 0, -1) :
    for j in [0 .. 70] :
        for k in [0 .. 20] :
            for l in [0 .. 20 - k] :
                s = j + (min(k + l, 10) - min(k, 10)) * i
                if s > 70 :
                    break
                f[i - 1][s][k + l] += f[i][j][k] * comb(k + l, k)
print f[0][70][20]
