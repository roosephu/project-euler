m = 12345
ans = 0
# for a in range(-n, n):
#     for b in range(-n, n):
#         for c in range(-n, n):
#             if a + b + c == 0 and max([abs(a), abs(b), abs(c)]) == 2:
#                 ans += 1
for t in range(1, m // 3 + 1):
        x = m - 3 * t + 1
            ans += t * x * (x + 1) * (x + 2) // 6
print ans
