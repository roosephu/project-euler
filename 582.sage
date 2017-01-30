ans = 0
LMT = 10**100

def dfs(u, v):
    global ans

    while u <= 2 * LMT:
        if v % 2 == k % 2 and v > k:
#             print (u, v), ((v - k) / 2, (v + k) / 2, u / 2)
            ans += 1
        u, v = u * 2 + v * 3, u * 1 + v * 2

for k in range(1, 101):
    print '---', k
    for u in range(1, k * 2 + 1, 1):
        if u <= k:
            continue
        v = floor(sqrt((1. * u * u - 1. * k * k) / 3))
        if u * u == 3 * v * v + k * k: # and v > k:
            dfs(u, v)
print ans

# for k in range(1, 101):
#     u, v = k, 0
#     for i in range(10):
#         u, v = u * 2 + v * 3, u * 1 + v * 2
#         print u, v, u * u - 3 * v * v