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
    ans = []
    for n in range(1, 20):
        cnt = search((1 << n) - 2, 0, n - 1)
        ans += [cnt]
        print n, cnt

    for i in range(4, 15):
        print 'guess', ans[i], ans[i] - ans[i - 1] * 2 - ans[i - 4]
    for width in range(6, 10):
        w, b = [], []
        for i in range(width):
            w += [ans[i:i + width]]
            b += [ans[i + width]]
        coef = matrix(w)^-1 * vector(b)
        print coef, vector(ans[width : width * 2]) * coef, ans[width * 2]
    return

main()
