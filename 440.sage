R = Integers(987898789)
n = 2
f = [0] * (n + 1)

def calc(n) :
    x = matrix(R, [0, 1])
    y = matrix(R, [[0, 1], 
                   [1, 10]])
    return (x * y^n)[0][1]

ans, single = 0, 0
for i in [1 .. n] :
    print 'phrase 1:', i
    for j in [1 .. n] :
        x = gcd(i, j)
        if is_odd(i // x) and is_odd(j // x) :
            f[x] += 1
        else :
            single += 1

for i in [1 .. n] :
    print 'phrase 2:', i
    x = matrix(R, [0, 1])
    y = matrix(R, [[0, 1], 
                   [1, 10]])
    for j in [1 .. n] :
        y = y^i
        ans += f[j] * (x * y)[0][1] # calc(i^j)
    if is_odd(i) :
        ans += single * 10
    else :
        ans += single * 1
print ans, f, single
