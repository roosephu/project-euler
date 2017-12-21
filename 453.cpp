#include "fmt/format.h"
#include <algorithm>
#include <NTL/ZZ.h>
#include <cmath>
using namespace fmt;
using namespace std;
using namespace NTL;

namespace PE453 {
    const int n = 4, m = 4, N = n + 10, M = m + 10;

    pair<int, int> p[N * M];

    int xp(pair<int, int> a, pair<int, int> b) {
        return a.first * b.second - a.second * b.first;
    }

    bool cmp(pair<int, int> a, pair<int, int> b) {
        return xp(a, b) < 0;
    }

    void main() {
        int T = 0;
        long Sx = 0, Sy = 0, Tx = 0, Ty = 0;
        for (int i = 0; i <= n; ++i) {
            for (int j = 0; j <= m; ++j) {
                p[T++] = {i, j};
                Tx += i;
                Ty += j;
            }
        }

        sort(p + 1, p + T, cmp);

        long bf = 0;
        for (int i = 0; i < T; ++i) {
            print("point: {} {}\n", p[i].first, p[i].second);
            for (int j = 0; j < i; ++j) {
                for (int k = 0; k < j; ++k) {
                    bf += abs(xp(p[i], p[j]) + xp(p[j], p[k]) + xp(p[k], p[i]));
                }
            }
        }
        print("bf = {}\n", bf);

        long ans = 0;
        for (int i = 0; i < T; ++i) {
            auto x = p[i].first, y = p[i].second;
            Tx -= x;
            Ty -= y;

            ans += (x * Sy - Sx * y) * (T - i - 1);
            ans += (y * Tx - Ty * x) * i;
            ans += Sx * Ty - Sy * Tx;

            if (i != 0) {
                // ans += GCD(x, y) * ;
            }

            Sx += x;
            Sy += y;
        }
        print("ans = {}\n", ans);
    }
}

int main() {
    PE453::main();
    return 0;
}
