def f(L, R, U, D, lu, ru, ld, rd, T={}):
    state = (L, R, U, D, lu, ru, ld, rd)
    if state not in T:
        ret = 0
        for l in range(L):
            for r in range(R):
                ret += f(l + 1, r + 1, U, 0, lu, ru, 0, 0) * f(L - l, R - r, U, D, ?, ?, ld, rd)

        T[state] = ret
    return T[state]
