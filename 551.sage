
dp = {}

def dfs(pre, length, init):
    global dp

    # print pre, length, init
    state = (pre, length, init)
    if state not in dp:
        if length == 0:
            if init == 1:
                # print 'got', pre
                return 1, pre
            return 0, init - 1

        total_cnt = 0
        for x in range(10):
            cnt, init = dfs(pre + x, length - 1, init)
            total_cnt += cnt
        dp[state] = total_cnt, init
    return dp[state]

def run(pre, length, init, total, now):
    if length == 0:
        return now + init - 1
    for x in range(10):
        cnt, feed = dfs(pre + x, length - 1, init)
        if cnt >= total:
            return run(pre + x, length - 1, init, total, now * 10 + x)
        init = feed
        total -= cnt

dfs(0, 18, 2)
print run(0, 18, 2, 2, 0)
