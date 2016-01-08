def score(x):
    t, n = x
    if t == 'S':
        return n
    if t == 'D':
        return 2 * n
    if t == 'T':
        return 3 * n
    return 0

darts = [(x, y) for x in ['D', 'S'] for y in [25]] + [(x, y) for x in ['S', 'D', 'T'] for y in range(1, 21)]

ans = 0
for a in darts + [('0', 0)]:
    for b in darts + [('0', 0)]:
        for c in darts:
            if a <= b and c[0] == 'D' and score(a) + score(b) + score(c) < 100:
                ans += 1
print ans
