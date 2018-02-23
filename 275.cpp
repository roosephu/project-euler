#include "fmt/format.h"
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <numeric>
using namespace fmt;
using namespace std;

namespace PE275 {
    const int maxN = 15, maxX = 36, O = 7;

    struct node {
        int moment;
        int tiles;
        long conn;

        node(int _moment, int _tiles, long _conn) : moment(_moment), tiles(_tiles), conn(_conn) { }
    };

    bool operator < (node a, node b) {
        if (a.conn != b.conn) return a.conn < b.conn;
        if (a.moment != b.moment) return a.moment < b.moment;
        return a.tiles < b.tiles;
    }

    map<node, long> f, g;
    long ans = 0;
    bool symmetry = false;

    int state[O * 2 + 1];

    void decode(long conn) {
        // print("   ");
        for (int i = 0; i <= O * 2; ++i) {
            state[i] = conn >> (i * 3) & 7;
            // print("{} ", state[i]);
        }
        // print("\n");
    }

    long encode(int *s, int bp) {
        int f[O * 2 + 1] = {0}, t = 0;
        long ret = 0, power = 1;
        for (int i = 0; i <= O * 2; ++i) {
            if (s[i] != 0 && f[s[i]] == 0) {
                f[s[i]] = ++t;
            }
            ret |= (long) f[s[i]] << (3 * i);
            s[i] = f[s[i]];
        }
        if (t > 7) return -1;
        // if (t > 7) {
        // for (int i = 0; i <= O * 2; ++i) {
        //     print("{} ", s[i]);
        // }
        // print("\n");
        // assert(0);
        // }
        return ret;
    }

    int get_min_connected(int *s) {
        int f[8] = {0};
        for (int i = 1; i <= 8; ++i) {
            f[i] = 100;
        }
        for (int i = 0, j = -1; i <= O * 2; ++i) {
            if (s[i]) {
                if (j >= 0 && s[i] != s[j]) {
                    int a = s[i], b = s[j];
                    f[a] = min(f[a], i - j);
                    f[b] = min(f[b], i - j);
                }
                j = i;
            }
        }
        int t = 0, mn = 100;
        for (int i = 1; i <= 8 && f[i] < 100; ++i) {
            t += f[i];
            mn = min(mn, f[i]);
        }
        t -= mn;

        static int x;
        x += 1;
        // if (x % 1000 == 0) {
        //     for (int i = 0; i <= O * 2; ++i) {
        //         print("{} ", s[i]);
        //     }
        //     print(": {}\n", t);
        // }
        return 0;
    }

    void insert(int moment, int tiles, int *state, int x, long value) {
        long conn = encode(state, x);
        if (tiles == maxN) {
            // if (moment1 != moment2) return;
            if (moment != 0 && !symmetry) return;
            for (int i = 0; i <= O * 2; ++i) {
                if (state[i] > 1) {
                    return;
                }
            }
            ans += value;
            return;
        }
        // if (moment1 > maxX) return;
        // if (get_min_connected(state) > maxN - tiles) return;
        // int mx = 0;
        // for (int i = 0; i <= O * 2; ++i) {
        //     if (mx < state[i]) {
        //         mx = state[i];
        //     }
        // }
        // if (tiles + max(2 * (mx - 1) - 1, 0) > maxN) return;
        f[node(moment, tiles, conn)] += value;
        // print("=> ");
        // for (int i = 0; i <= O * 2; ++i) {
        //     print("{} ", state[i]);
        // }
        // print("\n");
    }

    void add(int moment, int tiles, long value, int x) {
        int s[O * 2 + 1];

        copy(state, state + O * 2 + 1, s);
        if (x > -O && state[x + O] && state[x + O - 1]) {
            for (int i = 0; i <= O * 2; ++i) {
                if (s[i] == state[x + O]) {
                    s[i] = state[x + O - 1];
                }
            }
        } else if (x > -O && state[x + O - 1]) {
            s[x + O] = state[x + O - 1];
        } else if (!state[x + O]) {
            s[x + O] = O * 2;
        }
        insert(moment + x, tiles + 1 + (symmetry && x != 0), s, x, value);
    }

    void remove(int moment, int tiles, int value, int x) {
        int s[O * 2 + 1];
        copy(state, state + O * 2 + 1, s);
        if (s[x + O]) {
            bool found = false;
            for (int i = 0; i <= O * 2; ++i) {
                if (s[i] == s[x + O] && x + O != i) {
                    found = true;
                }
            }
            if (!found) {
                return;
            }
        }
        s[x + O] = 0;
        insert(moment, tiles, s, x, value);
    }

    void main() {
        long start = 1l << (O * 3);
        f[node(0, 0, start)] = 1;
        for (int y = 0; y < maxN; ++y) {
            for (int x = -O; x <= O; ++x) {
                print("=================== x = {}, y = {}, |f| = {}\n", x, y, f.size());
                g = f;
                f.clear();

                for (auto&& [k, v] : g) {
                    auto [moment, tiles, conn] = k;
                    // print("moment = {}, tiles = {}\n", moment, tiles);
                    decode(conn);

                    // if (abs(x * y) <= maxX)
                        add(moment, tiles, v, x);
                    remove(moment, tiles, v, x);
                }
            }
        }

        f.clear();
        symmetry = true;
        f[node(0, 0, start)] = 1;
        for (int y = 0; y < maxN; ++y) {
            for (int x = -O; x <= 0; ++x) {
                print("=================== x = {}, y = {}, |f| = {}\n", x, y, f.size());
                g = f;
                f.clear();

                for (auto&& [k, v] : g) {
                    auto [moment, tiles, conn] = k;
                    // print("moment = {}, tiles = {}\n", moment, tiles);
                    decode(conn);

                    // if (abs(x * y) <= maxX)
                        add(moment, tiles, v, x);
                    remove(moment, tiles, v, x);
                }
            }
        }
        print("ans = {}, * 2 = {}\n", ans / 2, ans);
    }
}

int main() {
    PE275::main();
    return 0;
}
