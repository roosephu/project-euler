#include "fmt/format.h"
#include <cmath>
#include <algorithm>
#include <map>
using namespace fmt;
using namespace std;

constexpr int n = 6;

long encode(int n, int *v) {
    long S = 0;
    for (int i = 0; i < n; ++i) {
        S = S << 2 | min(v[i], 2);
    }
    return S;
}

void decode(int n, int *v, long S) {
    for (int i = n - 1; i >= 0; --i) {
        v[i] = S & 3;
        S >>= 2;
    }
}

long dp(int n) {
    map<long, long> f, g;
    int status[20] = {0};

    for (int i = 1; i <= 9; ++i) {
        status[i % n] = 1;
        f[encode(n, status) << 1 | status[0]] += 1;
        status[i % n] = 0;
    }

    for (int len = 1; len < n; ++len) {
        g.clear();
        for (auto &it : f) {
            long key = it.first, value = it.second;
            int t = key & 1;

            decode(n, status, key >> 1);
            ++status[0];

            for (int i = 0; i <= 9; ++i) {
                int aux[20] = {0};
                for (int d = 0; d < n; ++d)
                    aux[(d * 10 + i) % n] += status[d];

                int nt = aux[0] + t;
                // print("{} {}\n", t, nt);
                if (nt <= 1) {
                    g[encode(n, aux) << 1 | nt] += value;
                }
            }
        }
        f = g;
        print("dp size: n = {}, len = {}, size = {}\n", n, len, f.size());
    }

    long ret = 0;
    for (auto &it : f) {
        if (it.first & 1) {
            ret += it.second;
        }
    }
    return ret;
}

int main() {
    long ans = 0;
    for (int i = 1; i <= 19; ++i) {
        long cur = dp(i);
        print("{}: {}\n", i, cur);
        ans += cur;
    }
    print("ans = {}\n", ans);

    // f[0][0][0][1] = 1;
    // for (int i = 0; i < n; ++i) {
    //     for (int b = 0; b < 2; ++b) {
    //         for (int m = 0; m < n; ++m) {
    //             for (int S2 = 0; S2 < State2; ++S2) {
    //                 for (int S3 = 0; S3 < State3; ++S3) {
    //                     if (f[i][b][m][S2][S3] == 0)
    //                         continue;
    //                     int v2[p2] = {0}, v3[p3] = {0};
    //                     decode(S2, v2, p2, 2);
    //                     decode(S3, v3, p3, 3);
    //                     print("i = {}, b = {}, m = {}, S = {}, v = [{}, {}]\n", i, b, m, S2, v[0], v[1]);
    //                     for (int x = 0; x <= 9; ++x) {
    //                         if (x != 0 || i != 0) {
    //                             int y = (m * 10 + x) % n;
    //                             int n_i = i + 1;
    //                             int n_S2 = encode(v2, p2, 2);
    //                             int n_S3 = encode(v3, p3, 3);
    //                             int n_m = y;
    //                             int n_b = b + v2[0];
    //                             // print("| i = {}, b = {}, m = {}, S = {}\n", n_i, n_b, n_m, n_S);
    //                             if (n_b <= 1) {
    //                                 f[n_i][n_b][n_m][n_S2][n_S3] += f[i][b][m][S2][S3];
    //                             }
    //                         }
    //                         rotate(v2, v2 + p2 - 1, v2 + p2);
    //                         rotate(v3, v3 + p3 - 1, v3 + p3);
    //                     }
    //                 }
    //             }
    //         }
    //     }
    // }
    // long ans = 0;
    // for (int m = 0; m < n; ++m)
    //     for (int S = 0; S < State; ++S)
    //         ans += f[n][1][m][S];

    // long ans2 = 0;
    // for (int a = 2; a <= 2; ++a)
    //     for (int b = 0; b <= 9; ++b)
    //         for (int c = 0; c <= 9; ++c)
    //             for (int d = 0; d <= 9; ++d) {
    //                 int x = (a % n == 0) +
    //                         (b % n == 0) +
    //                         ((a * 10 + b) % n == 0) +
    //                         (c % n == 0) +
    //                         ((b * 10 + c) % n == 0) +
    //                         ((a * 100 + b * 10 + c) % n == 0) +
    //                         (d % n == 0) +
    //                         ((c * 10 + d) % n == 0) +
    //                         ((b * 100 + c * 10 + d) % n == 0) +
    //                         ((a * 1000 + b * 100 + c * 10 + d) % n == 0);
    //                 if (x == 1) {
    //                     ++ans2;
    //                     // print("{}\n", a * 1000 + b * 100 + c * 10 + d);
    //                 }
    //             }
    // print("ans2 = {}\n", ans2);

    // print("n = {}, f(n) = {}\n", n, ans);
    return 0;
}

/*
ans:
1: 9
2: 20
3: 360
4: 2701
5: 4096
6:
7: 161022
8:
9: 2136960
10: 0
11: 71101800
12:
13: 1057516028
14:
15:
16:
17: 195741994241
18:
19: 2253334981970
 */