from itertools import *

perm = {x: x for x in range(10)}
perm[9] = 6
print perm

ans = 0
for cube1 in combinations(range(10), 6):
    for cube2 in combinations(range(10), 6):
        if cube2 > cube1:
            break
        p = map(lambda x: perm[x], cube1)
        q = map(lambda x: perm[x], cube2)

        check = True
        for i in range(1, 10):
            x, y = i * i // 10, i * i % 10
            x, y = perm[x], perm[y]
            if not ((x in p and y in q) or (x in q and y in p)):
                check = False
                break
        if check:
            ans += 1
    # print cube1
print ans
