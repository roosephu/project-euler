# for p in permutations(n) :
#     s, t = 0, []
#     for i, x in enumerate(p) :
#         if i == 0 or () :
        
# ans = 0
# for i in [1 .. 111] :
#     ans += 1.0 / i
# print ans

# y = log(x) + euler_gamma

# for i in [1 .. 20] :
#     y = integral(y, x)

# def finite(x) :
#     cmd, p, q = x
#     if cmd == 0 :               # H_n C(n, p)
#         return [(0, )]
#     else :                      # q * C(n, p)
#         return [(1, p + 1, q)]

def C(n, k) :
    t = 1.0
    for i in [1 .. k] :
        t = t * n / i
        n -= 1
    return t

n, m = 1e14, 20

n += m
ans = (log(n) + euler_gamma) * C(n, m)
for k in [1 .. m] :
    ans -= C(n, m) / k

print ans.n(digits = 20)
