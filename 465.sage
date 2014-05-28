def f(n) :
    t = 0
    for i in [1 .. n] :
        if n % i == 0 :
            t += euler_phi(i) * n / i
    return t

ans = 0
for i in [1 .. 100] :
    ans += f(i)
    print ans, f(i), euler_phi(i)
