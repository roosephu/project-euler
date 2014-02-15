
coef = {}
comb = {}

def S(n, k) :                   # \sum_{x = 1}^n x^k
    ret = 0
    P = 1
    for i in [1 .. k + 1] :
        P *= n
        ret += P * coef[k + 1 - i] * comb[(k + 1, i)]
    return ret / (k + 1)

def dfs(n, lmt, A, B, C) :              # \sum_{x=1}^n x^a \floor{A x + C}{B} ^b constraint a + b <= lmt
    f = {}
    # if A * n + C < B :
    #     for i in [0 .. lmt] :
    #         for j in [0 .. lmt - i] :
    #             f[(i, j)] = 0
    if A == 0 :
        p = [(C // B)^i for i in [0 .. lmt]]
        q = [S(n, i) for i in [0 .. lmt]]
        for i in [0 .. lmt] :
            for j in [0 .. lmt - i] :
                f[(i, j)] = p[j] * q[i]
    elif A >= B :
        t = A // B
        w = dfs(n, lmt, A % B, B, C)
        for i in [0 .. lmt] :
            for j in [0 .. lmt - i] :
                f[(i, j)] = 0
                for x in [0 .. j] :
                    f[(i, j)] += comb[(i, x)] * t^i * w[(i + x, j - x)]
    elif C >= B :
        t = C // B
        w = dfs(n, lmt, A, B, C % B)
        for i in [0 .. lmt] :
            for j in [0 .. lmt - i] :
                f[(i, j)] = 0
                for x in [0 .. j] :
                    f[(i, j)] += comb[(i, x)] * t^i * w[(i, j - x)]
    else :                      # hardest
        w = dfs(n, lmt, B, A, B - C - 1)
        nn = (A * n + C) // B - 1
        for a in [0 .. lmt] :
            for b in [0 .. lmt - a] :
                T = 0
                for i in [0 .. b - 1] :
                    T += comb[(b, i)] * S(n, a) * S(nn, i)
                    for j in [1 .. a + 1] :
                        T -= 1 / (a + 1) * comb[(a + 1, j)] * coef[a + 1 - j] * w[(i, j)]
                f[(a, b)] = T
    print "parameters:", n, lmt, A, B, C
    print 'result:', f
    return f

def bf(n, lmt, A, B, C) :
    f = {}
    for a in [0 .. lmt] :
        for b in [0 .. lmt - a] :
            t = 0
            for i in [0 .. n] :
                t += i^a * ((A * i + C) // B)^b
            f[(a, b)] = t
    return f

def init(s) :
    for i in [0 .. s + 1] :
        for j in [0 .. s + 1] :
            if i < j :
                comb[(i, j)] = 0
            elif j == 0 :
                comb[(i, j)] = 1
            else :
                comb[(i, j)] = comb[(i - 1, j - 1)] + comb[(i - 1, j)]

    coef[0] = 1
    for k in [1 .. s] :
        coef[k] = 1
        for i in [0 .. k - 1] :
            coef[k] -= comb[(k + 1, i)] * coef[i] / (1 + k)

init(10)
print S(10, 0)
print bf(10, 0, 2, 4, 3), dfs(10, 0, 2, 4, 3)
