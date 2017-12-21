f = {}

cnt = 0
def calc(s, f={}):
    global cnt

    cnt += 1
    s = list(sorted([x for x in s if x > 0]))
    if cnt > 100:
        return 0
    if len(s) == 0:
        return 1
    T = tuple(s)
    if T not in f:
        val = calc([x - 1 for x in s])
        ret = val
        for i in range(len(s)):
            ret += calc(s[:max(i - 1, 0)] + [s[i] - 1] + s[min(i + 1, len(s)):]) - val
        f[T] = ret * 2
        print(T, ret)
    return f[T]

print(calc([2, 2]))