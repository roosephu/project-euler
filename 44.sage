P = set()
for i in [1 .. 10000] :
    P.add(i * (3 * i - 1) / 2)

x = sorted(list(P))
# print x
for i in x :
    for j in x :
        if i < j :
            break
        if (i + j) in P and (i - j) in P :
            print i, j, i - j
