def get_min_num(ps):
    ret = 1
    for x, y in ps:
        ret *= x ** y
    return ret

ans = 0
LMT = 10**18
def dfs(n, rn, rs):
    # print 'a', n, rn, rs
    if n * rn > LMT or gcd(n, rs) != 1:
        return
    if rn == 1 and rs == 1: # and is_odd(rs):
        global ans
        print '------', n, rs, sigma(n) / n
        ans += n
        # return
    if rs == 1:
        return
    p = prime_factors(rs)[0]
    e = 1
    while rs % p**(e + 1) == 0:
        e += 1
    for i in range(e, 100):
        new_n = n * p**i
        if new_n > LMT:
            break
        new_rn = rn * p**i
        new_rs = rs * (p**(i + 1) - 1) // (p - 1)
        k = gcd(new_rn, new_rs)
        # print new_n, new_rn // k, new_rs // k, p, i
        dfs(new_n, new_rn // k, new_rs // k)

for x in range(3, 17, 2):
    dfs(1, x, 2)
print 'ans = %d' % (ans)
