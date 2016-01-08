a = 1
b = 1

def ok(s):
    x = sorted(set(list(s)))
    return len(x) == 9 and x[0] == '1' and x[8] == '9'

cnt = 2
MOD = 10**9
aa, bb = 1, 1
while cnt < 10**6:
    a, b = b, (a + b) % MOD
    aa, bb = bb, aa + bb
    cnt += 1
    x = str(b)
    if ok(x[-9:]):
        xx = str(bb)
        print cnt, xx[-9:], xx[:9]
        if ok(xx[:9]):
            break
