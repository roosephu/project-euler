#include "fmt/format.h"
#include <vector>
#include <algorithm>
#include <set>
#include <numeric>
using namespace fmt;
using namespace std;

namespace PE275 {
    const int maxN = 15, maxX = 36, O = 6;

    struct node {
        int c[maxN];
    };

    int layer(int L, int o) {
        int t = 0;
        for (int i = 0; i < maxN; ++i) {
            if ((o & L) >> i & 1) {
                while ((L >> i & 1) && i < maxN) {
                    t |= 1 << i;
                    ++i;
                }
            }
        }
        for (int i = maxN - 1; i >= 0; --i) {
            if ((o & L) >> i & 1) {
                while ((L >> i & 1) && i >= 0) {
                    t |= 1 << i;
                    --i;
                }
            }
        }
        return t;
    }

    int cnt = 0, nums = 100;
    vector<vector<int>> G[maxN + 10];
    vector<int> S[maxN + 10];
    int lmt = 0, found = 0;
    int max_height[maxN + 10], get[maxN + 10];

    void generate(vector<int> L, int rem) {
        if (rem == 0) {
            int curN = accumulate(L.begin(), L.end(), 0);
            G[curN].push_back(L);
            // for (auto x : L) {
            //     print("{} ", x);
            // }
            // print("\n");
            nums = min(curN, nums);
            cnt += 1;
            return;
        }
        int n = L.size() + 1, m = maxN - accumulate(L.begin(), L.end(), 0);
        for (int i = 1; i <= rem / n && i <= m; ++i) {
            vector<int> l = L;
            l.push_back(i);
            generate(l, rem - i * n);
        }
    }

    int popcnt(int n) {
        return n ? popcnt(n >> 1) + (n & 1) : 0;
    }

    int maps[maxN * 2 + 10], visited[maxN * 2 + 10];

    void dfs(int i, int j) {
        if (i < 0 || j < 0 || (maps[i] >> j & 1) == 0) return;
        if (visited[i] >> j & 1) return;
        visited[i] |= 1 << j;
        dfs(i + 1, j);
        dfs(i - 1, j);
        dfs(i, j + 1);
        dfs(i, j - 1);
    }

    int get_min_conn(int t) {
        int ret = 0, R = -1;
        for (int i = 0, j = -1; i < maxN; ++i) {
            if ((t >> i & 1)) {
                if (j != -1 && j != i - 1) {
                    ret += i - j;
                }
                j = i;
            }
        }
        return ret;
    }

    int glob_R, checked = 0;

    void search(vector<int> &g, int depth, int last, bool check, int conn) {
        maps[depth + O] = last;
        if (depth == g.size()) {
            if (last != conn) return;
            if (check) {
                ++checked;
                // if (checked % 1000000 == 0) {
                //     print("____\n");
                    // for (int i = 0; i <= O * 2; ++i) {
                    //     print("{:15b} {:15b}\n", maps[i], visited[i]);
                    // }
                // }
                for (int i = 0; i <= O * 2; ++i) {
                    visited[i] = 0;
                }
                dfs(O, 0);
                // print("check {:7b}\n", visited[O]);
                // if (visited[O] == 63) {
                // }
                bool symmetric = true;
                for (int i = 0; i <= O * 2; ++i) {
                    if (visited[i] != maps[i]) {
                        return;
                    }
                    symmetric &= maps[i] == maps[2 * O - i];
                }
                ++found;
                if (symmetric) ++found;
            } else {
                for (int i = 0; i <= O * 2; ++i) {
                    visited[i] = 0;
                }
                for (int y = 0; y < maxN; ++y) {
                    if (maps[O] >> y & 1) {
                        dfs(O, y);
                    }
                }

                for (int i = 0; i <= O * 2; ++i) {
                    if (visited[i] != maps[i]) {
                        return;
                    }
                }

                for (int i = 1; i <= O; ++i) {
                    swap(maps[O + i], maps[O - i]);
                }
                for (auto y : G[glob_R]) {
                    search(y, 0, maps[O], true, maps[O]);
                }
                for (int i = 1; i <= O; ++i) {
                    swap(maps[O + i], maps[O - i]);
                }
            }
            return;
        }
        int sum = 0;
        for (int i = depth + 1; i < g.size(); ++i) {
            sum += g[i];
        }
        for (auto t : S[g[depth]]) {
            // if (t > lmt * 32) break;
            if ((t & last) && (last & ~(conn | layer(last, t))) == 0) {
                int new_conn = layer(t, conn);
                // print("conn = {:10b}, t = {:10b}, nc = {:10b}\n", conn, t, new_conn);
                // if ((last & ~(conn | t)) != 0) continue;
                // if (get_min_conn(new_conn) > sum) continue;
                search(g, depth + 1, t, check, new_conn);
                maps[depth + O + 1] = 0;
            }
        }
    }

    void main() {
        for (int i = 1; i <= (1 << maxN); ++i) {
            S[popcnt(i)].push_back(i);
        }

        long ans = 0;
        for (int x = 0; x <= maxX; ++x) {
            print("=============\n");
            cnt = 0, nums = 100;
            for (int i = 0; i <= maxN; ++i) {
                G[i].clear();
            }
            generate(vector<int>(), x);
            print("x = {}, cnt = {}, num = {}\n", x, cnt, nums);
            int nl = nums, nr = 0;
            for (int i = nl; i <= maxN - nl; ++i) {
                if (G[i].size() != 0) {
                    max_height[i] = 0;
                    for (auto g : G[i]) {
                        int h = 0;
                        for (int x = g.size() - 1; x >= 0; --x) {
                            if (g[x] == 1) {
                                h = 0;
                            } else {
                                h += g[x] - 2;
                            }
                        }
                        max_height[i] = max(max_height[i], h);
                        nr = i;
                    }
                    print("[# = {}, S = {}, h = {}] ", i, G[i].size(), max_height[i]);
                }
            }
            print("\n");
            for (int M = max(1, maxN - 2 * nr); M <= maxN - nl * 2; ++M) {
                lmt = 0;
                for (int L = max(nl, maxN - M - nr); L <= min(nr, maxN - nl - M); ++L) {
                    lmt = max(lmt, max_height[L] + max_height[maxN - L - M]);
                }
                lmt += M;
                print("height limit = {}\n", lmt);
                found = 0, checked = 0;
                for (auto s : S[M]) {
                    if (s >= (1 << lmt)) break;
                    if (~s & 1) continue;
                    // print("-----\n");
                    // print("search: {:7b}\n", s);

                    for (int L = max(nl, maxN - nr - M); L <= min(nr, maxN - nl - M); ++L) {
                        glob_R = maxN - L - M;
                        for (auto x : G[L]) {
                            search(x, 0, s, false, s);
                        }
                    }
                }
                ans += found;
                print("checked = {}, found = {}\n", checked, found);
            }
        }
        print("ans = {}\n", ans / 2);
    }

    int f[20][20];

    set<unsigned long> Q;

    unsigned long inv(unsigned long M) {
        unsigned long ret = 0;
        for (int x = -O; x <= O; ++x) {
            for (int y = 0; y < maxN; ++y) {
                int l = f[x + O][y];
                if (l >= 0 && (M >> l & 1)) {
                    ret |= 1ull << f[-x + O][y];
                }
            }
        }
        return ret;
    }

    void dfs(unsigned long M, int loc, int d, int moment) {
        if (loc < 0 || (M >> loc & 1) || abs(moment) > maxX) return;
        M |= 1ull << loc;
        if (Q.count(M)) return;
        Q.insert(M), Q.insert(inv(M));
        if (d == maxN) {
            // int moment = 0, absm = 0;
            // for (int x = -O; x <= O; ++x) {
            //     for (int y = 0; y < maxN; ++y) {
            //         int l = f[x + O][y];
            //         if (l >= 0 && (M >> l & 1)) {
            //             moment += x;
            //             absm += abs(x);
            //         }
            //     }
            // }
            if (moment == 0) {
                // print("---\n");
                // for (int x = -4; x <= 4; ++x) {
                //     for (int y = 0; y < maxN; ++y) {
                //         int l = f[x + 4][y];
                //         print("{}", l >= 0 && (M >> l & 1) ? 1 : 0);
                //     }
                //     print("\n");
                // }
                found += 1;
            }
            return;
        }
        for (int x = -O; x <= O; ++x) {
            for (int y = 0; y < maxN; ++y) {
                int l = f[x + O][y];
                if (l >= 0 && (M >> l & 1)) {
                    if (x > -O) dfs(M, f[x + O - 1][y], d + 1, moment + x - 1);
                    if (x < O) dfs(M, f[x + O + 1][y], d + 1, moment + x + 1);
                    if (y > 0) dfs(M, f[x + O][y - 1], d + 1, moment + x);
                    dfs(M, f[x + O][y + 1], d + 1, moment + x);
                }
            }
        }
    }

    void main1() {
        int t = 0;
        for (int x = -O; x <= O; ++x) {
            for (int y = 0; y < maxN; ++y) {
                if (abs(x * y) <= 4) {
                    f[x + O][y] = t++;
                } else {
                    f[x + O][y] = -1;
                }
            }
        }
        print("t = {}\n", t);

        found = 0;
        dfs(0, f[0 + O][0], 1, 0);
        print("found = {}\n", found);
    }
}

int main() {
    PE275::main();
    return 0;
}
