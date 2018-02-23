#include "fmt/format.h"
#include <set>
#include <cmath>
#include <NTL/ZZ.h>
using namespace fmt;
using namespace std;
using namespace NTL;

namespace PE617 {
    const long N = 1e18;

    long L[10], top = 0;
    long limit;

    long root(long y, int e) {
        if (e == 2) return SqrRoot(y);
        long x = min((long)pow(y, 1. / e) + 1, limit);
        while (x && (pow(x - 1e-3, e) > y || power_long(x, e) > y)) --x;
        return x;
    }

    int defac(long x, int e) {
        int ret = 0;
        // while (true) {
        //     long y = root(x, e);
        //     if (power_long(y, e) == x) {
        //         x = y;
        //         ++ret;
        //     } else {
        //         break;
        //     }
        // }
        top = 0;
        while (x <= N) {
            ++top, L[top] = x;
            if (x > limit) break;
            x = power_long(x, e);
        }
        return ret;
    }

    bool test(long n, int e, long s) {
        set<long> S;
        while (S.count(s) == 0) {
            S.insert(s);
            s = power_long(s, e);
            s = min(s, n - s);
            if (s > limit || s <= 1) {
                return false;
            }
        }
        return true;
    }

    void main() {
        long ans = SqrRoot(N);
        if (ans * ans + ans > N) --ans; // exclude w = Sqrt(N)
        --ans; // exclude w = 1
        // for (int i = 2; i * i + i <= N; ++i) {
        //     print("e = 2, n = {}, start = {}\n", i * i + i, i);
        // }
        for (int e = 2; e <= 70; ++e) {
            set<pair<long, long>> S;
            double _limit = pow(N, 1. / e);
            if (_limit < 2) break;
            limit = _limit + 1e-4;
            while (pow(limit -     1e-4, e) >  N || power_long(limit    , e) >  N) --limit;
            while (pow(limit + 1 + 1e-4, e) <= N && power_long(limit + 1, e) <= N) ++limit;

            print("e = {}, limit = {}, test = {}\n", e, limit, pow(8 + 1 + 1e-4, 21) <= N);
            long lim = limit;
            if (e == 2) lim = SqrRoot(lim);
            for (int i = 2; i <= lim; ++i) {
                if (e > 10)
                    print("{}\n", i);
                if (power_long(root(i, e), e) == i) {
                    // print("root = {}, i = {}, e = {}\n", root(i, e), i, e);
                    continue;
                }
                defac(i, e);
                if (top == 2 && L[1] + L[2] <= N) {
                    ans += 1;
                    continue;
                }
                for (int j = 1; j <= top; ++j) {
                    for (int k = 1; k < j; ++k) {
                        for (int s = 1; s < j; ++s) {
                            if (L[j] + L[k] <= N && (e != 2 || s != k || s + 1 != j)) {
                                // assert(S.count({L[j] + L[k], L[s]}) == 0);
                                // S.insert({L[j] + L[k], L[s]});
                                // print("e = {}, n = {}, start = {}\n", e, L[j] + L[k], L[s]);
                                // if (!test(L[j] + L[k], e, L[s])) {
                                //     // print("xxx, limit = {}\n", limit);
                                //     return;
                                // }
                                ++ans;
                            }
                        }
                    }
                }
            }
        }

        print("ans = {}\n", ans);
    }
}

int main() {
    PE617::main();
    return 0;
}
