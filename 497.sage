R = Integers(10**9)

# n, k, A, B, C = 3, 20, 4, 9, 17 # 2, 5, 1, 3, 5 # 3, 7, 2, 4, 6

ans = 0
t = vector(R, [0, 0, 0, 1, 0, 0])
for i in range(1, 10000 + 1):
    print i, ans
    n, k, A, B, C = i, R(10)**i, R(3)**i, R(6)**i, R(9)**i

    #  0   1   2   3   4   5
    # [ab, bc, ca, ac, cb, ba]
    if i != 1:
        fst = vector(R, [t[3], t[4], t[5], t[0], t[1], t[2]])
        snd = vector(R, [t[5], t[3], t[4], t[1], t[2], t[0]])
        t = fst + vector(R, [0, 0, 0, 1, 1, 1]) + snd

    def walk(n, x, y, b): # b = [x < y]
        if b:
            x = y - x
            n = y - 1
        else:
            n = n - y
            x = x - y

        return n * n - (n - x) * (n - x)

    wt = [walk(k, A, B, True), walk(k, B, C, True), walk(k, C, A, False), walk(k, A, C, True), walk(k, C, B, False), walk(k, B, A, False)]
    ans += vector(wt) * (t + vector(R, [0, 0, 0, 0, 0, 1]))

print ans
