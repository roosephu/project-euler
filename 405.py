f = [[0, 0, 2, 1]]

for _ in range(4) :
    g = []
    for x1, y1, x2, y2 in f :
        if x2 - x1 == 1 :
            g += [[x1 * 2, y1 * 2, x2 * 2, y1 * 2 + 1]]
            g += [[x1 * 2, y2 * 2 - 1, x2 * 2, y2 * 2]]
            g += [[x1 * 2, y1 * 2 + 1, x1 * 2 + 1, y2 * 2 - 1]]
            g += [[x2 * 2 - 1, y1 * 2 + 1, x2 * 2, y2 * 2 - 1]]
        else :
            g += [[x1 * 2, y1 * 2, x1 * 2 + 1, y2 * 2]]
            g += [[x2 * 2 - 1, y1 * 2, x2 * 2, y2 * 2]]
            g += [[x1 * 2 + 1, y1 * 2, x2 * 2 - 1, y1 * 2 + 1]]
            g += [[x1 * 2 + 1, y2 * 2 - 1, x2 * 2 - 1, y2 * 2]]
    f = g[0:]

    G = {}
    for a, b, c, d in f :
        G[(a, c)] = G.get((a, c), 0) + 1
        G[(a, d)] = G.get((a, d), 0) + 1
        G[(b, c)] = G.get((b, c), 0) + 1
        G[(b, d)] = G.get((b, d), 0) + 1

    ans = 0
    for (x, y), t in G.items() :
        if t == 4 :
            print(x, y)
            ans += 1
    print(ans)
    # print(f)
