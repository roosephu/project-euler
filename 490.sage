def search(state, cur, last):
    if state == 0:
        return 1 if cur == last else 0
    # print state, cur, last
    ret = 0
    for i in range(-3, 4):
        v = cur + i
        if 0 <= v <= last and (state >> v & 1) == 1:
            ret += search(state ^^ (1 << v), v, last)
    return ret

def main():
    # ans = []
    # for n in range(1, 20):
    #     cnt = search((1 << n) - 2, 0, n - 1)
    #     ans += [cnt]
    #     print n, cnt

    ans = [0, 0, 0, 0, 1, 1, 1, 2, 6] #, 14, 28, 56, 118, 254, 541, 1140, 2401, 5074, 10738, 22711, 48001, 101447, 214446, 453355, 958395, 2025963, 4282685, 9053286, 19138115, 40456779, 85522862]
    # for i in range(1, len(ans)):
    #     ans[i] += ans[i - 1]
    # for i in range(8, 50):
    #     next = ans[i - 1] * 2 - ans[i - 2] + ans[i - 3] * 2 + ans[i - 4] + ans[i - 5] - ans[i - 7] - ans[i - 8]
    #     ans += [next]
        # (-1, -1, 0, 1, 1, 2, -1, 2)
    equ = -1 - x + x^3 + x^4 + 2 * x^5 - x^6 + 2 * x^7 - x^8
    print equ

    coef = [-1, -1, 0, 1, 1, 2, -1, 2]
    idx = {}
    for i in range(8):
        for j in range(i, 8):
            for k in range(j, 8):
                cur = len(idx)
                idx[(i, j, k)] = cur
    cur = len(idx)
    idx['sum'] = cur

    size = len(idx)
    mat = [[0] * size for i in range(size)]
    init = [0] * size
    print 'matrix size = %d' % (size)

    mat[idx['sum']][idx['sum']] += 1
    mat[idx['sum']][idx[(4, 4, 4)]] += 1

    for i in range(8):
        for j in range(i, 8):
            for k in range(j, 8):
                cur = idx[(i, j, k)]

                def dfs(L, Y, c):
                    if len(L) == 0:
                        y = tuple(sorted(Y))
                        src = idx[y]
                        mat[cur][src] += c
                        return
                    x, xs = L[0], L[1:]
                    if x != 7:
                        dfs(xs, Y + (x + 1, ), c)
                    else:
                        for i, nc in enumerate(coef):
                            dfs(xs, Y + (i, ), c * nc)

                dfs([i, j, k], (), 1)

    for i in range(8):
        for j in range(i, 8):
            for k in range(j, 8):
                init[idx[(i, j, k)]] += ans[i] * ans[j] * ans[k]

    R = Integers(10**9)
    mat = matrix(R, mat)
    vec = vector(R, init)
    next = mat**(10**14) * vec
    # for i in range(8):
    #     for j in range(i, 8):
    #         for k in range(j, 8):
    #             print i, j, k, next[idx[(i, j, k)]]
    print next

    # print roots(equ)
    # for width in range(6, 25):
    #     w, b = [], []
    #     for i in range(width):
    #         w += [powered[i:i + width]]
    #         b += [powered[i + width]]
    #     coef = matrix(w)^-1 * vector(b)
    #     print coef, vector(powered[width : width * 2]) * coef, powered[width * 2]
    return

main()
