#include "fmt/format.h"
#include <algorithm>
#include <NTL/ZZ.h>
using namespace fmt;
using namespace std;
using namespace NTL;

namespace PE606 {

    const long n = 1e12, N = 2e6 + 10;
    const long MOD = 1e9;

    long f[N];

    void main1() {
        f[1] = 1;
        long ans = 0;
        for (int i = 1; i <= n; ++i) {
            // print("{} {}\n", i, f[i]);
            for (int j = i + i; j <= n; j += i) {
                f[j] = min(f[i] + f[j], 255);
            }
            if (f[i] == 252) {
                print("{}: ", i);
                for (int a = i, b = 2; a != 1; ++b) {
                    while (a % b == 0) {
                        a /= b;
                        print(" {}", b);
                    }
                }
                print("\n");
                ans += i;
            }
        }
        print("ans = {}\n", ans);
    }

    long basis[N];
    int R, idx;

    int get_index(long p) {
        return p > R ? n / p : (idx + 1 - p);
    }

    int main() {
        idx = 0;
        R = SqrRoot(n);
        for (long i = 1; n / i > R; ++i) {
            basis[++idx] = n / i;
        }
        for (long i = R; i; --i) {
            basis[++idx] = i;
        }

        for (long i = 1; i <= idx; ++i) {
            long h = basis[i];
            if (h % 2 == 0)
                h = (h / 2 % MOD) * (h % MOD + 1) % MOD;
            else
                h = (h + 1) / 2 % MOD * (h % MOD) % MOD;
            f[i] = h * h % MOD;
            if (i != get_index(basis[i])) {
                print("!!!\n");
            }
        }

        for (long p = 2; p <= R; ++p) {
            if (!ProbPrime(p)) {
                continue;
            }
            for (int i = 1; basis[i] >= p * p; ++i) {
                long delta = (f[get_index(basis[i] / p)] + MOD - f[get_index(p) + 1]) % MOD;
                // print("{} {}, delta = {}\n", i, basis[i], delta);
                f[i] = (f[i] + MOD - p * p % MOD * p % MOD * delta % MOD) % MOD;
            }
            // for (int i = 1; i <= idx; ++i) {
            //     print("{} ", f[i]);
            // }
            // print("\n");
        }
        // for (int i = 1; i <= idx; ++i) {
        //     print("{} {}\n", basis[i], f[i]);
        // }

        long ans = 0;
        for (long p = 2; p <= R; ++p) {
            if (ProbPrime(p)) {
                ans += p * p % MOD * p % MOD * (f[get_index(n / p)] + MOD - f[get_index(p)]) % MOD;
            }
        }
        print("ans = {}\n", (ans % MOD + MOD) % MOD);
    }
}

int main() {
    PE606::main();
    return 0;
}