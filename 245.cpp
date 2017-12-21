#include "fmt/format.h"
#include <NTL/ZZ.h>
#include <algorithm>
using namespace fmt;
using namespace NTL;
using namespace std;

namespace PE245 {
    const int B = 1e1;
    const int MAX_P = 1e5;

    long phi[B], rem[B];

    const long N = 2e11;
    int T;
    int primes[MAX_P];

    void BF1() {
        long L = 1, R = L + B - 1;
        for (int i = 0; i < B; ++i) {
            phi[i] = L + i;
            rem[i] = L + i;
        }

        PrimeSeq gen;
        for (int u; (u = gen.next()) < B; ) {
            for (long i = max((L - 1) / u, 1) + 1; i * u <= R; ++i) {
                int t = i * u - L;
                phi[t] = phi[t] / u * (u - 1);
                rem[t] /= u;
                if (rem[t] % u == 0) {
                    rem[t] = 0;
                }
            }
        }

        for (int i = 0; i < B; ++i) {
            long t = L + i;
            if (rem[i] == t || rem[i] == 0) {
                continue;
            }
            if (rem[i] > 1) {
                phi[i] = phi[i] / rem[i] * (rem[i] - 1);
            }
            if ((t - 1) % (t - phi[i]) == 0) {
                print("{}, ", t);
            }
        }
        print("\n");
    }

    long ans = 0;
    int cnt = 0, mp;
    void dfs(long n, long phi, int d) {
        if (GCD(n, phi) != 1) return;
        if (n > 1) {
            long lp = primes[d + 1], rp = N / n;
            long lb = (n * lp - 1) / (n * lp - (lp - 1) * phi);
            long rb = (n * rp - 1) / (n * rp - (rp - 1) * phi);
            if (lb % 2 == 1) ++lb;
            for (long T = lb; T <= rb; T += 2) {
                if (n == mp && (T * T - T + 1) % (n - T) != 0) continue;
                if (GCD(n, T) != 1) continue;
                // consider last prime
                long w = phi * T;
                long p_mod_n = PowerMod(w % n, phi - 1, n) + 1;
                // if (n == 31 && T == 24) print("... {} {}, {}\n", w, p_mod_n, (p_mod_n - 1) * w % n);
                for (long p = p_mod_n; p <= w + 1 && p <= N / n; p += n) {
                    if ((w + 1) % p == 0 && p > primes[d] && ProbPrime(p)) {
                        ++cnt;
                        print("found {}: {}, T = {}, w = {}, n = {}, lb = {}, rb = {}, mp = {}\n", cnt, n * p, T, w, n, lb, rb, mp);
                        ans += n * p;
                    }
                }
            }
        }
        for (; ++d <= primes[0]; ) {
            int p = primes[d];
            // if (T % p == 0) continue;
            if (n > N / p / p) break;
            dfs(n * p, phi * (p - 1), d);
        }
    }

    void main() {
        PrimeSeq gen;
        for (int u; (u = gen.next()) <= 5e5; ++u) {
            ++primes[0];
            primes[primes[0]] = u;
        }
        for (int i = 1; i <= primes[0]; ++i) {
            long p = primes[i];
            if (p * p > N) break;
            mp = p;
            dfs(p, p - 1, i);
        }
        // for (T = 2; T <= 4e4; T += 2) {
        //     int fp = 1;
        //     while (primes[fp] <= T)
        //         ++fp;
        //     dfs(1, 1, fp - 1);
        // }
        print("ans = {}\n", ans);
    }
}

int main() {
    PE245::main();
    return 0;
}
