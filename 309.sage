LMT = 10^6 - 1
sqrt_lmt = 10^3

G = [[] for i in [1 .. LMT + 1]]
for i in [1 .. sqrt_lmt] :
    print i
    for j in [1 .. (i - 1)] :
        if gcd(i, j) == 1 :
            a = i * i - j * j
            b = 2 * i * j
            c = i * i + j * j
            for x in [1 .. LMT // c] :
                G[a * x] += [(b * x, c * x)]
                G[b * x] += [(a * x, c * x)]

# m = 0
# for j, i in enumerate(G) :
#     if len(i) > m :
#         m = len(i)
#         print m, j

M = set()
ans = 0
for w in [1 .. LMT] :
    G[w].sort()
    print w, len(G[w])
    # print w
    for p, x in G[w] :
        for q, y in G[w] :
            if x <= y :
                break
            # print s, p, q
            if (p * q) / (p + q) == 1 :
                T = (x, y, w)
                if T not in M :
                    M.add(T)
                    ans += 1
                    # print x, y, s.denominator(), w
print ans
