from collections import defaultdict

f = defaultdict(float)
f[((0, 0, 0, 0, 0), (0, 0, 0, 0, 0), 0)] = 1.

for rnd in range(50):
    print rnd, len(f)
    g = defaultdict(int)
    for (L, R, diff), val in f.items():
        L, R = list(L), list(R)
        p = val / 10
        for v in range(1, 11):
            score = 0
            if v in L:
                newL = L
                score += 1
            else:
                newL = L[1:] + [v]

            if v in R:
                newR = filter(lambda x: x != v, R) + [v]
                score -= 1
            else:
                newR = R[1:] + [v]

            collect, label = [], {}
            for i in newL + newR:
                if i == 0:
                    collect += [0]
                else:
                    if i not in label:
                        new_label = len(label) + 1
                        label[i] = new_label
                    collect += [label[i]]

            # print L, R, v, collect, newL, newR
            g[(tuple(collect[:5]), tuple(collect[5:]), diff + score)] += p

    f = g

ans = 0
for (_, _, diff), prob in f.items():
    ans += prob * abs(diff)
print "%.9f" % ans
