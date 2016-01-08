import string

mod = 14
N = 100
ans = 0

def rep(x):
    s = ""
    sum = 0
    while x > 0:
        s = string.hexdigits[x % mod] + s
        sum += x % mod
        x /= mod
    return s, sum

Q = []
for i in range(1, mod):
    if i * i % mod == i:
        Q += [i]
        ans += i
        print rep(i)[0]

for n in range(1, N):
    print n
    mpow = mod**n
    P = []
    for x in Q:
        y = x
        for i in range(mod):
            if y * y / mpow % mod == i:
                P += [y]
                if i != 0:
                    s, sum = rep(y)
                    ans += sum
                    # print s
            y += mpow
    Q = P

print 'ans = %d' % (ans)
print rep(604557993)
