from itertools import *
from math import *

with open('p098_words.txt') as f:
    words = []
    for l in f:
        for t in l.split(','):
            words += [t[1:-1]]

def permute(w, d):
    if d[w[0]] == 0:
        return 2
    ret = 0
    for c in list(w):
        ret = ret * 10 + d[c]
    return ret

def is_sqr(n):
    # if n == 1296:
    #     print 'xxx'
    x = int(sqrt(n))
    return x * x == n

ans = 0
# words = ['RACE', 'CARE']
for w1 in words:
    for w2 in words:
        if w1 != w2 and sorted(list(w1)) == sorted(list(w2)):
            t = list(set(list(w1)))
            print w1, w2, t
            for perm in permutations(range(10), len(t)):
                d = {t[i]: perm[i] for i in range(len(t))}
                s1 = permute(w1, d)
                s2 = permute(w2, d)
                # if perm[0] == 2:
                #     print s1, s2
                # print perm
                if is_sqr(s1) and is_sqr(s2):
                    ans = max(max(s1, s2), ans)
                    print w1, w2, s1, s2

print ans
