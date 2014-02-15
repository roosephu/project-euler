
def chk(x) :
    s = str(x)
    y = x // 10
    while y > 0 :
        S = ""
        cnt = 1
        while len(S) < len(s) :
            S += str(cnt * y)
            cnt += 1
        
        if S == s :
            print x, y
            return True
        y = y // 10
    return False

ans = 0
for x in permutations([1 .. 9]) :
    v = sum([j * 10 ** i for i, j in enumerate(x)])
    if chk(v) :
        ans = max(ans, v)
