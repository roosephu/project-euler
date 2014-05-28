x, y = 0, 1.0
for i in range(2, 100000) :
    f = 2 * x / i + 1
    x = y
    y += f
    print(i, f / i)
