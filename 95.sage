LMT = 10^6
f, g = dict(), dict()

def dfs(x, d) :
    print x, sigma(x) - x
    if x > LMT or x <= 1 :
        return -1
    if x in g :
        return d - g[x]
    if x in f :
        return f[x]
    g[x] = d
    f[x] = dfs(sigma(x) - x, d + 1)
    del g[x]
    return f[x]

dfs(5916, 0)
# ans = 0
# for i in [1 .. LMT] :
#     x = dfs(i, 0)
#     if x > ans :
#         ans = x
#         print ans, i
