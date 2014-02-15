def f(x, alpha) :
    r = x / sin(alpha) / sqrt(2)
    return (1 - (x * r * cos(pi / 4 - alpha) - r * r * alpha)) / (2 - 2 * x + 2 * alpha * r)

eps = 1e-16

def dfs2(L, R, alpha) :
    while R - L > eps :
        lm = ((L * 2 + R) / 3).n(digits = 25)
        mr = ((L + R * 2) / 3).n(digits = 25)
        if f(lm, alpha) > f(mr, alpha) :
            R = mr
        else :
            L = lm
    return f((L + R) / 2, alpha)

def dfs1(L, R) :
    while R - L > eps :
        print L, R
        lm = ((L * 2 + R) / 3).n(digits = 25)
        mr = ((L + R * 2) / 3).n(digits = 25)
        if dfs2(0, 1.0, lm) > dfs2(0, 1.0, mr) :
            R = mr
        else :
            L = lm
    return dfs2(0, 1, (L + R) / 2)

print dfs1(0, pi / 4).n(digits = 20)
# tri_search(lambda x : tri_search(lambda y : f(x, y)))
