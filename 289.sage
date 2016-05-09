from collections import defaultdict

def main():

    n, m = 6, 10
    G = defaultdict(list)

    for i in range(n):
        for j in range(m):
            for k in range(4):
                G[(i, j, k)] += [(i, j, (k + 1) % 4)]
            if i < n - 1:
                G[(i, j, 3)] += [(i + 1, j, 1)]
                if j == 0:
                    G[(i, j, 0)] += [(i + 1, j, 0)]
                if j == m - 1:
                    G[(i, j, 2)] += [(i + 1, j, 2)]
            if j < m - 1:
                G[(i, j, 2)] += [(i, j + 1, 0)]
                if i == 0:
                    G[(i, j, 1)] += [(i, j + 1, 1)]
                if i == n - 1:
                    G[(i, j, 3)] += [(i, j + 1, 3)]

    g = defaultdict(list)
    for x, val in G.items():
        for y in val:
            g[x] += y
            g[y] += x

    def get_label(i, j, k):
        return 4 * i * m + 4 * j + k

    f = defaultdict(int) # state = {x: degree}
    for i in range(n):
        for j in range(m):
            for k in range(4):
                ff = defaultdict(int)
                x = (i, j, k)
                neighbors = g[x]
                for state, val in f.items():

                    def dfs(dep, S, rem):
                        if dep < 0:
                            if rem > 0:
                                # push
                                S = S.copy()
                                S[x] = rem
                            ff[tuple(S.items())] += val
                            return
                        y = neighbors[dep]
                        dfs(dep - 1, S, rem)
                        if rem > 0 and S[y] > 0:
                            S = S.copy()
                            if S[y] > 1:
                                S[y] -= 1
                            else:
                                del S[y]
                            dfs(dep, S, rem - 1)

                    dfs(len(neighbors) - 1, dict(state), 2)
                f = ff
