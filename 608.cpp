#include "fmt/format.h"
#include <map>
#include <NTL/ZZ.h>
using namespace std;
using namespace NTL;
using namespace fmt;

namespace PE608 {
    const int n = 200;
    const long m = 1e12;
    const int maxR = 2.1e6;
    const int MOD = 1e9 + 7;

    long basis[maxR], f[maxR], num_primes[maxR];
    long g[65], R;

    int get_index(long x) {
        return x <= R ? 2 * R - x : (m / x);
    }

    int get_power(int p, int n) {
        int ret = 0;
        for (; n /= p; )
            ret += n;
        return ret;
    }

    long real_f(long x, int p) {
        int t = get_index(x);
        if (x <= p) return f[t];
        return f[t] + 2 * (num_primes[t] - num_primes[get_index(p)]) % MOD;
    }

    void main() {
        R = SqrRoot(m);
        int cnt = 0;
        for (long i = 1; m / i > R; ++i)
            basis[++cnt] = m / i;
        for (int i = R; i; --i)
            basis[++cnt] = i;
        // for (int i = 1; i <= cnt; ++i) {
        //     if (get_index(basis[i]) != i)
        //         print("!!! {} {}\n", get_index(basis[i]), i);
        // }

        for (int i = 1; i <= cnt; ++i) {
            num_primes[i] = basis[i] - 1;
        }
        // for (int i = 1; i < cnt; ++i) {
        //     for (int v = basis[i + 1] + 1; v <= basis[i]; ++v)
        //         if (v > R && ProbPrime(v))
        //             f[basis[i]] += 2;
        // }
        // f[1] = 1;
        // for (int i = cnt - 1; i; --i) {
        //     f[basis[i]] += f[basis[i + 1]];
        //     // print("init {} = {}\n", basis[i], f[basis[i]]);
        // }

        // long ans = 0;
        // for (int i = 1; i <= m; ++i) {
        //     ans += m / i;
        // }
        // print("bf = {}\n", ans);
        for (long x = 2; x <= R; ++x) {
            if (ProbPrime(x)) {
                print("current = {}\n", x);
                for (int i = 1; i <= cnt; ++i) {
                    long y = basis[i];
                    if (x * x > y)
                        break;
                    auto a = num_primes[get_index(y / x)];
                    auto b = num_primes[get_index(x - 1)];
                    num_primes[i] -= a - b;
                }
            }
        }
        for (int i = 1; i <= cnt; ++i) {
            num_primes[i] %= MOD;
            // print("{} {}\n", basis[i], num_primes[i]);
        }
        for (int i = 1; i <= cnt; ++i) {
            f[i] = 1;
            // if (basis[i] >= R) {
            //     f[i] += 2 * (num_primes[get_index(basis[i])] - num_primes[R]);
            // }
            // print("init {} {}\n", basis[i], f[i]);
        }

        for (long p = R; p; --p) {
            if (ProbPrime(p)) {
                print("current = {}\n", p);

                int t = p > n ? 0 : get_power(p, n);
                for (int e = 0; e <= 60; ++e)
                    g[e] = (e + 1) * (t + 1) + t * (t + 1) / 2;

                for (int i = 1; i <= cnt; ++i) {
                    long y = basis[i];
                    if (t == 0 && p * p > y)
                        break;
                    long v = 0; // 2 * (num_primes[get_index(y)] - num_primes[p]);
                    for (int e = 0; y; ++e) {
                        v += real_f(y, p) * g[e] % MOD;
                        y /= p;
                    }
                    if (basis[i] >= p)
                        v -= 2 * (num_primes[i] - num_primes[get_index(p)] + 1) % MOD;
                    f[i] = (v + MOD) % MOD;
                    // print("update {} = {}\n", basis[i], v);
                }
            }
        }
        print("ans = {}\n", real_f(m, 1));
    }
}

int main() {
    PE608::main();
    return 0;
}