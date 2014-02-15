P = [i for i in primes(102)]
ps = []
x = 1
for i in P :
    x *= i
    ps += [x]

print len(P)
n = prod(P)
lmt = floor(sqrt(n))
ans = 0
F = {}

def dfs(dep, x) :
    if (dep, x) in F :
        return F[(dep, x)]
    if x == 1 or dep < 0 :
        return 1
    a = dfs(dep - 1, x)
    b = dfs(dep - 1, floor(x / P[dep])) * P[dep]
    if a < b :
        a = b
    F[(dep, x)] = a
    return a

# while N % a != 0 :
#     a = floor(N / floor(N / a)) + 1
#     print a
# print N, a
print n, P
ans = dfs(len(P) - 1, lmt)
print n % ans, ans, len(F)


