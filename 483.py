from fractions import gcd
import numpy as np

n = 100

factorial = []
last = 1
for i in range(n + 1):
    factorial.append(last)
    last = last * (i + 1)

maxSum = np.zeros(n + 1)
for i in range(1, n + 1):
    maxSum[i:] = np.maximum(maxSum[i:], maxSum[:-i] + np.log(i))
# print('maxSum', maxSum)

# maxLCM = [1]

# cur = 0
# def dfs2(n, t, lcm):
#     global cur

#     if n > t * (t + 1) // 2:
#         return
#     if lcm * maxLCM[n] <= cur:
#         return
#     if n == 0:
#         if lcm > cur:
#             cur = lcm
#         return
#     dfs2(n    , t - 1, lcm)
#     if t <= n:
#         dfs2(n - t, t - 1, lcm * t // gcd(lcm, t))

# for i in range(1, n + 1):
#     cur = 0
#     for j in range(1, i + 1):
#         dfs2(i - j, j, j)
#     maxLCM.append(cur)

# maxLCM = np.log(maxLCM)
# print('maxLCM', maxLCM)
print('maxSUM', maxSum)

cycles = []

def info(S):
    deno = 1.
    period = 1.
    cnt = np.zeros(n + 1)
    for a in S:
        cnt[a] += a
        deno *= cnt[a]

    T = []
    for i in range(1, n + 1):
        if cnt[i] != 0:
            cnt[i] = i
            for j in T:
                cnt[i] = cnt[i] // gcd(cnt[i], j)
            period *= cnt[i]
            T.append(i)
        # period = period * a // gcd(period, a)
    return deno, period

print(info([19, 17, 16, 13, 11, 9, 7, 5, 2, 1]))
# print(np.exp(maxSum[n]))
# print(info([11, 9, 8, 7, 5]))
thres = 1e8
nodes = 0

def dfs(x, t, S):
    global thres, nodes
    if x > t * (t + 1) // 2: return

    deno, period = info(S)
    if period**2 / deno * np.exp(maxSum[x]) <= thres:
        return
    # if len(S) == 1:
    #     print(S)
    nodes += 1
    if x == 0:

        # print(S)
        # print(S, deno, period)
        cycles.append((period**2 / deno, period, deno, S))
        print(period**2 / deno, S)
        assert len(cycles) <= 100
        return
    t = min(x, t)
    for i in reversed(range(1, t + 1)):
        dfs(x - i, i, S + [i])

dfs(n, n, [])
cycles = list(reversed(sorted(cycles)))
print(len(cycles), nodes)
for x in cycles[:10]:
    print(x)
test = 0
for x in cycles:
    test += 1. / x[2]
print(test)
