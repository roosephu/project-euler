#include "fmt/format.h"
#include "fmt/ostream.h"
#include <set>
#include <vector>
#include <NTL/lzz_p.h>
using namespace fmt;
using namespace std;
using namespace NTL;

// const int m = 15;

// int f[m + 2][(1 << m) + 10];

// vector<int> decode(int x) {
//     vector<int> ret;
//     for (int i = 0, v = -1; x; x >>= 1, ++i)
//         if (x & 1) {
//             ret.push_back(i - v - 1);
//             v = i;
//         }
//     return ret;
// }

// int test() {
//     for (int o = 0; o < m; ++o) {
//         for (int i = 1; i < (1 << m); ++i) {
//             if ((i >> o & 1) == 0)
//                 continue;

//             set<int> S;
//             for (int a = 0, x = -1; a < m; ++a) {
//                 if ((i >> a) & 1) {
//                     if (x == -1)
//                         S.insert(f[o][i ^ (1 << a)]);
//                     for (int t = x + 1; t < a; ++t) {
//                         S.insert(f[a == o ? t : o][i ^ (1 << a) ^ (1 << t)]);
//                     }
//                     x = a;
//                 }
//             }
//             for (; S.count(f[o][i]) != 0; )
//                 ++f[o][i];

//         }
//     }
//     // for (int i = 1; i < (1 << m); ++i)
//     //     for (int o = 0; o < m; ++o)
//     //         if (i >> o & 1) {
//     //             int t = i >> o >> 1;
//     //             if ((t & (t - 1)) != 0 || t == 0)
//     //                 continue;
//     //             print("o = {}, {:06b}: {}\n", o, i, f[o][i]);
//     //         }
//     // for (int i = 0; i < (1 << 5); ++i) {
//         // print("{:06b}: {}, {}, {}, {}\n", i, f[6][3 << 5 | i], f[7][3 << 6 | i], f[8][3 << 7 | i], f[9][3 << 8 | i]);
//         // print("{:010b}: {}, {:010b}: {}, {:010b}: {}\n", 7 << 5 | i, f[5][7 << 3 | i], 7 << 6 | i, f[6][7 << 6 | i], 7 << 7 | i, f[7][7 << 7 | i]);
//     // }

//     int G[20][20] = {{0}};
//     for (int i = 0; i < (1 << m); ++i) {
//         // int S = i << 3 | 6;
//         // int o = 2;
//         for (int o = 0; o < m; ++o) {
//             int S = i;
//             if ((S >> o & 1) == 0)
//                 continue;
//             int T = S & ((1 << o) - 1);
//             if (T == 0)
//                 continue;

//             // if (f[o][S] != 0)
//                 // continue;
//             if ((T & (T - 1)) != 0) {
//                 S = S << 1;
//                 // continue;
//             } else {
//                 S = S << 1 | 1;
//                 continue;
//             }
//             // if (__builtin_parity(S) != 1)
//                 // continue;
//             auto d = decode(S);

//             int sg = 0;
//             for (int t = d.size() - 1; t >= 0; t -= 2)
//                 sg ^= d[t]; // + (t == 0 && (T & (T - 1)) != 0);
//             // sg += S == (S >> o << o);
//             // sg = max(((sg + 1) ^ 1) - 1, 0);
//             // if (f[o][S] != sg || 1) {
//             //     print("T = {}, H = {} of [", f[o][S], sg);
//             //     for (auto t : d)
//             //         print("{} ", t);
//             //     print("]\n");
//             // }
//             ++G[f[o][i]][sg];
//             // print("{:010b}: {}\n", i << 1 | 1, f[0][i << 1 | 1]);

//         }
//     }
//     for (int i = 0; i < 10; ++i) {
//         for (int j = 0; j < 10; ++j) {
//             print("{:4} ", G[i][j]);
//         }
//         print("\n");
//     }
//     return 0;
// }

const int n = 1e6, m = 100, N = n + 10;

zz_p f[N], g[N], fac[N], caf[N];

zz_p cb(int n, int m) {
    if (n < m) return zz_p(0);
    return fac[n] * caf[m] * caf[n - m];
}

void dp(zz_p *f, int n, int m) {
    f[0] = 1;
    for (int b = 20; b >= 0; --b) { // 2^b > n
        for (int i = n; i; --i) {
            for (int j = 2; j <= m && (j << b) <= i; j += 2) {
                f[i] += f[i - (j << b)] * cb(m, j);
            }
        }
    }
}

int main() {
    zz_p::init(1000036000099ll);

    fac[0] = 1;
    for (int i = 1; i <= n; ++i)
        fac[i] = fac[i - 1] * i;
    caf[n] = zz_p(1) / fac[n];
    for (int i = n; i >= 1; --i)
        caf[i - 1] = caf[i] * i;

    zz_p total = cb(n, m + 1) * (m + 1);
    dp(f, n, m / 2 + 1);
    dp(g, n, m / 2);

    zz_p ans = total;
    for (int i = 0; i <= n - m; ++i) { // silver is the second one
        ans -= cb(n - 1 - m / 2 - i, m / 2) * f[i];
        // print("i = {}, f[i] = {}\n", i, f[i]);
    }
    // print("ans = {}\n", ans);
    for (int i = 1; i <= n - m + 1; ++i) { // silver is behind the second one
        ans -= cb(n - m / 2 - i, m / 2) * (f[i] - g[i]) * (m - 1);
        // print("i = {}, ?[i] = {}\n", i, f[i] - g[i]);
    }
    print("total = {}, ans = {}\n", total, ans);

    return 0;
}