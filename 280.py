import numpy as np

n = 5
m = n * n
trans = np.zeros((m, m), dtype=np.float)
print trans.shape

for i in range(n):
    for j in range(n):
        pos = i * n + j
        if i > 0:
            trans[pos, pos - n] = 1
        if i < n - 1:
            trans[pos, pos + n] = 1
        if j > 0:
            trans[pos, pos - 1] = 1
        if j < n - 1:
            trans[pos, pos + 1] = 1
        trans[pos] /= np.sum(trans[pos])

iterations = 10000
def get_prob(endpoints):
    t = len(endpoints)
    prob = np.zeros((m, t), dtype=np.float)
    dist = np.zeros((m, t), dtype=np.float)

    for _ in range(iterations):
        prob = trans.dot(prob)
        dist = trans.dot(dist) + 1
        for i, endpoint in enumerate(endpoints):
            prob[endpoint] *= 0
            dist[endpoint] *= 0
            prob[endpoint, i] = 1

    prob.resize((n, n, t))
    dist.resize((n, n, t))
    print endpoints, np.sum(prob[2, 2])
    return (prob, dist)

tables = [() for i in range(1 << n)]
for state in range(1 << n):
    endpoints = []
    for i in range(n):
        if state >> i & 1:
            endpoints += [i]
    tables[state] = get_prob(endpoints)

totalProb, ans, sig = 0, 0, 0
def dfs(upper, lower, x, y, probability, cost):
    global totalProb, ans, sig

    sig = sig + 1
    current = sig

    if upper == 0 and lower == 0:
        totalProb += probability
        ans += probability * cost
        return
    prob, dist = tables[lower]

    cnt = 0
    for i in range(n):
        if lower >> i & 1:
            p, d = prob[x, y, cnt], dist[x, y, cnt]
            dfs(lower ^ (1 << i), upper, n - 1, i, probability * p, cost + d)
            cnt += 1
    # if sent < 0.9999:
        # print 'xxx', current, sent, lower, (lower >> 0 & 1), (lower >> 1 & 1), cnt, np.sum(prob[x, y])

dfs((1 << n) - 1, (1 << n) - 1, (n - 1) // 2, (n - 1) // 2, 1, 0)
print totalProb, ans
