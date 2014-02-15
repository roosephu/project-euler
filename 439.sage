def bf(n) :
    ans = 0
    for i in [1 .. n] :
        for j in [1 .. n] :
            ans += sum(divisors(i * j))
    return ans

def sphi(n) :
    ans = 0
    for i in [1 .. n] :
        ans += sum(divisors(i))
    return ans

print sphi(100)
# f = {}
# for i in [1 .. 30] :
#     f[i] = bf(i)
#     a = 0
#     for j in [1 .. i] :
#         a += f[i // j] * j
#     b = sphi(i)^2
#     print f[i]
