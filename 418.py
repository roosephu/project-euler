def calc(x, y) :
    t = 0
    while x != 0 :
        x = x // y
        t += x
    return t

def cbrt(x) :
    L, R = 1, x
    while L < R :
        m = (L + R + 1) // 2
        if m ** 3 <= x :
            L = m
        else :
            R = m - 1
    return R

n = 43
primes = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43]
cnt = []
prod = 1
for i in range(1, n + 1) :
    prod *= i
for i in primes :
    cnt += [calc(n, i)]
LMT = cbrt(prod)
As = 0

def search(now, dep) :
    global As
    if now > LMT :
        return 
    if dep == len(primes) :
        As += 1
        if As % 100000 == 0 :
            print(As)
        return
    for i in range(cnt[dep] + 1) :
        search(now, dep + 1)
        now *= primes[dep]
        if now > LMT :
            return

search(1, 0)
print(cnt, As)

