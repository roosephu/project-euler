#include "lib.h"
#include <map>
#include <string>
#include <unordered_map>

namespace PE289 {
    const int n = 100, m = 10; // n >= m
    const long MOD = 1e10;
    int connections[] = {1111, 1114, 1133, 1134, 1131, 1211, 1214, 1221, 1222, 1224, 1231, 1232, 1233, 1234};

    map<long, long> f, g;
    map<pair<long, int>, vector<long>> cache;

    int state[20];
    int cnt;

    void decode(long s) {
        for (int i = 0; i < (m + 3); ++i) {
            state[i] = s >> (i * 4) & 15;
        }
    }

    long merge(long s, long x, long y) {
        if (s == -1) return s;
        for (int i = 0; s >> (i * 4); ++i) {
            long w = s >> (i * 4) & 15;
            if (w == x) {
                s ^= (x ^ y) << (i * 4);
            }
        }
        return s;
    }

    int find(long s, int k) {
        long ret = 0;
        for (int i = 0; i < (m + 4); ++i) {
            ret += (s & 15) == k;
            s >>= 4;
        }
        return ret;
    }

    long rep(long s) {
        long ret = 0, t = 0, f[20] = {0};
        for (int i = 0; s >> (i * 4); ++i) {
            long x = s >> (i * 4) & 15;
            if (!f[x]) {
                ++t;
                f[x] = t;
            }
            ret |= (long) (f[x] - 1) << (4 * i);
        }
        assert(t <= 14);
        return ret;
    }

    vector<long> init_cache(long k, int x, int y) {
        cnt += 1;
        vector<long> S;
        decode(k);
        for (int C : connections) {
            long a = C / 1000 - 1, b = C / 100 % 10 - 1, c = C / 10 % 10 - 1, d = C / 1 % 10 - 1;
            long indices[] = {a, b, c, d};
            int new_color = y == m || x == n ? 0 : 15;
            int colors[] = {state[y], state[y + 1], state[y + 2], new_color};
            long kk = k << 4 | new_color;
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 4; ++j) {
                    if (colors[i] == 0 && (colors[j] == 0) != (indices[i] == indices[j])) {
                        kk = -1;
                    }
                }
            }
            // if (x == 1 && y == 1 && k == 03210 && C == 1232) {
            //     print("!!! kk = {:05o}\n", kk);
            // }
            // if (kk != -1)
            for (int i = 0; i < 4 && kk != -1; ++i) {
                if (i == indices[i]) continue;
                int c_src = kk >> (4 * (y + i + 1)) & 15;
                int c_dst = kk >> (4 * (y + indices[i] + 1)) & 15;
                if (i == 3) c_src = new_color;
                if (c_src == 0) continue;
                if (c_src == c_dst || !c_src || !c_dst)
                    kk = -1;
                kk = merge(kk, c_src, c_dst);
            }
            if (kk != -1) {
                long cur = kk & 15; kk = kk >> 4;
                long old = (kk >> ((y + 1) * 4)) & 15;
                if (find(kk, old) > 1 || old == cur || (x == n && y == m)) {
                    kk ^= (cur ^ old) << (4 * (y + 1));
                    if (y == m) kk = kk << 4;
                // print("{} {} {} {}, kk = {:05o}\n", a, b, c, d, kk);
                    // print("{:05o} => {:05o}, [{}, {}, {}, {}]\n", k, rep(kk), a, b, c, d);
                    S.push_back(rep(kk));
                    // (f[rep(kk)] += v) %= MOD;
                }
            }
        }
        return S;
    }

    void main() {
        f[0] = 1;
        for (int x = 0; x <= n; ++x) {
            for (int y = 0; y <= m; ++y) {
                print("================= x = {}, y = {}, |f| = {}, cnt = {}\n", x, y, f.size(), cnt);
                g = f;
                f.clear();
                for (auto [k, v] : g) {
                    // print("current: {:05o}, v = {}\n", k, v);
                    if (x == n) {
                        for (auto kk : init_cache(k, x, y)) {
                            (f[kk] += v) %= MOD;
                        }
                    } else {
                        pair<long, int> S = {k, y};
                        if (!cache.count(S)) {
                            cache[S] = init_cache(k, x, y);
                        }
                        for (auto kk : cache[S]) {
                            (f[kk] += v) %= MOD;
                        }
                    }
                }
            }
        }
        long ans = f[0];
        // long ans = 0;
        // for (auto [k, v] : f) {
        //     print("{:05o}: {}\n", k, v);
        //     ans += v;
        // }
        print("ans = {}\n", ans);
    }
}

int main() {
    PE289::main();
    return 0;
}
