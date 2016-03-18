n = 100000

ans = 0
# for i in range(1, n + 1):
#     print i
#     for j in range(1, i + 1):
#         S, T = [], []
#         for x in range(1, j + 1):
#             if i % x == 0 and j % (x + 1) == 0:
#                 # i -> i / x * (x + 1)
#                 # j -> j / (x + 1) * x
#                 # S += [j / (x + 1) * x]
#                 ans += 1
#             if i % (x + 1) == 0 and j % x == 0: # and i / (x + 1) != j / x:
#                 # T += [min(j / x * (x + 1), i / (x + 1) * x)]
#                 ans += 1
#         X = set(S + T)
#         ans += len(X)
#         if len(X) > 0:
#             print i, j, S, T

for x in range(1, n + 1):
    for t in range(1, n / x + 10):
        if t * x <= n:
            ans += int(t * x / (x + 1))
        if t * (x + 1) <= n:
            ans += int(t * (x + 1) / x)

for i in range(2, n + 1): # delete the case (w, h) -> (h, w)
    ans -= int(n / i)
for x in range(1, n + 1):
    for y in range(1, min(x + 1, n / x + 10)):
        ans -= int(n / x / (y + 1))
for x in range(1, n + 1):
    for y in range(1, min(x, n / (x + 1) + 10)):
        ans -= int(n / (x + 1) / (y + 1))
print ans
