from fractions import Fraction

ans = 0
def dfs(x1, y1, x2, y2):
    global ans

    if x1 * 100 > y1 or y1 * y2 > 100000:
        return
    if x1 == 0 and y2 >= 1000:
        return
    if x1 != 0 and x1 * y2 + x2 * y1 < y1 * y2 * 50:
        print x1, y1, x2, y2
        ans += 1
    u = x1 + x2
    v = y1 + y2
    dfs(x1, y1, u, v)
    dfs(u, v, x2, y2)

dfs(0, 1, 1, 1)
print ans
# fs = []
# stk = []
# for q in range(1, 20000):
#     for p in range(1, q // 50 + 1):
#         if gcd(p, q) == 1:
#             fs += [Fraction(p, q)]
# fs.sort()

# L = Fraction(int(1), int(100))
# ans = 0
# for x in fs:
#     # print x, stk
#     while len(stk) > 0:
#         y = stk[-1]
#         z = (x + y) / int(2)
#         if z < L and z.denominator < 100000000:
#             ans += 1
#             # w = z.limit_denominator(max(x.denominator, y.denominator))
#             # assert w == x or w == y
#             # if (w == x or w == y) and w.denominator < 100000000:
#             #     ans += 1
#                 # print x, y, z
#             # else:
#                 # print [x, y, z]
#         if y.denominator >= x.denominator:
#             stk.pop()
#         else:
#             break
#         # test z
#     stk += [x]

# print ans
