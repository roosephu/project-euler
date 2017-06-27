#include "fmt/format.h"
#include <NTL/ZZ.h>
#include <map>
using namespace fmt;
using namespace std;
using namespace NTL;

namespace PE598 {
    const int n = 100;

    int m = 0;
    int f[n];
    map<pair<long, long>, long> F[50];

    bool ok(long a, long b, long t) {
        for (int i = f[t] - 1; i > 1; --i) {
            while (a % i == 0)
                a /= i;
            while (b % i == 0)
                b /= i;
        }
        return a == 1 && b == 1;
    }

    long dfs(long a, long b, long t) {
        long g = GCD(a, b);
        a /= g, b /= g;

        if (t > m) {
            // if (a == b) {
            //     print("find\n");
            // }
            return a == b;
        }

        pair<long, long> S{a, b};
        if (F[t].count(S) == 0) {
            if (!ok(a, b, t))
                F[t][S] = 0;
            else {
                long ret = 0;
                for (int i = 1; i < f[t]; ++i) {
                    ret += dfs(a * i, b * (f[t] - i), t + 1);
                }
                F[t][S] = ret;
            }
        }
        return F[t][S];
    }

    void main() {
        long p = 1;

        PrimeSeq gen;
        for (int u; (u = gen.next()) <= n; ) {
            ++m;
            f[m] = 2;
            for (int i = n; i /= u; ) {
                f[m] += i;
            }
            p *= f[m];
            print("{} {}\n", f[m], p);
        }
        long ans = dfs(1, 1, 1);
        print("ans = {}\n", ans / 2);
        for (int i = 1; i <= m; ++i) {
            print("|F[i]| = {}\n", F[i].size());
        }
    }
}

int main() {
    PE598::main();
    return 0;
}