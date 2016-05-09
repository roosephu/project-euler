r = solve(x^3 - x^2 - 1, x, solution_dict=True)[2][x]
print n(r, 100)

f = {0: 1, 1: r, 2: r^2}
for i in range(3, 100):
    f[i] = f[i - 1] + f[i - 3]
for i in range(-1, -100, -1):
    f[i] = f[i + 3] - f[i + 2]

# for k in f.keys():
#     f[k] = n(f[k], 512)

eps = 1e-70

def count(d, w):
    if w == 0:
        return 0
    if w < f[d]:
        return count(d - 1, w)
    return count(d - 1, w - f[d]) + 1

ans = 0
for i in range(1, 50 + 1):
    w = i * i
    ans += count(99, w)
print ans
