
def remove(cnt, i):
    ret = cnt[:]
    ret[i] -= 1
    for j in range(i + 1, 5):
        ret[j] += 1
    return ret

F = {}
def dp(dep, cnt):
    if dep == 0:
        return 0
    state = tuple(cnt)

    if state not in F:
        ans = 0.
        tot = sum(cnt)
        if tot == 1:
            ans = 1.
        for i in range(5):
            if cnt[i] != 0:
                ans += dp(dep - 1, remove(cnt, i)) * cnt[i] / tot
        F[state] = ans
    return F[state]

print dp(16, [1, 0, 0, 0, 0]) - 2
