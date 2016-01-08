S = {}
for i in range(1, 10000):
    h = tuple(sorted(list(str(i * i * i))))
    if h in S:
        S[h] += [i * i * i]
        if len(S[h]) == 5:
            print S[h]
            break
    else:
        S[h] = [i * i * i]
