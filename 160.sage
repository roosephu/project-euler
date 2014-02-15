# for i in [1 .. 1000000] :
#     a = i * 5
#     x = (a + 1) * (a + 2) * (a + 3) * (a + 4) % 100000
#     if x == 24 :
#         print a, i
#         break

mod = 10^5
R = Integers(mod)

def bonus(n) :
    ret = R(1)
    w = n % 5
    n -= w
    for i in [1 .. min(mod * 2, n)] :
        if i % 5 == 0 :
            continue
        t = i
        if i % 10 in [4, 8] :
            t /= 2
        ret *= R(t)^((n - i) // (mod * 2) + 1)
    for i in [1 .. w] :
        ret *= R(n + i)
    return ret

def bf(n) :
    x = factorial(n)
    while x % 10 == 0 :
        x /= 10
    return x % mod
    
def solve(n) :
    if n <= 5 :
        return bf(n)
    return solve(n // 5) * bonus(n)

print solve(10^12)
