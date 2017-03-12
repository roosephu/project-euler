#include "fmt/format.h"
#include <vector>
#include <NTL/ZZ.h>
#include <cstdlib>
using namespace fmt;
using namespace NTL;
using namespace std;

namespace PE526 {
    const int MAX_PRIMES = 10000000;
    const int PRIMES = 11;
    const long N = 1e16;

    int primes[MAX_PRIMES];
    long dvs[9] = {1, 6, 1, 2, 15, 2, 1, 6, 1};
    int inv[100][100], rems[PRIMES + 10][PRIMES + 10];
    long ans = 49601160286750947ll; // 9997194587108081
    // long LOWER_BOUND = 9.91075046516362e15;
    long LOWER_BOUND = 9.997e15;
    // double rate = 4.916;
    long cnt = 0, step, total;

    void dfs(int depth, long lcm, long val) {
        if (depth > PRIMES) {
            cnt += 1;
            if (cnt % step == 0)
                fmt::fprintf(stderr, "\r#%.6f: lcm = %lld, val = %lld", 1. * cnt / total, lcm, val);
            // print("lcm = {}, val = {}\n", lcm, val);
            // exit(0);
            long last = N - N % lcm + val;
            if (last > N) last -= lcm;
            for (; last >= LOWER_BOUND; last -= lcm) {
                long x = last;
                if (ProbPrime(x + 0) && ProbPrime(x + 2) && ProbPrime(x + 6) && ProbPrime(x + 8)) {
                    if (((x + 3) % 4 == 0 && ProbPrime((x + 3) / 4) && ProbPrime((x + 5) / 2) && ProbPrime((x + 1) / 6) && ProbPrime((x + 7) / 24)) ||
                        ((x + 5) % 4 == 0 && ProbPrime((x + 5) / 4) && ProbPrime((x + 3) / 2) && ProbPrime((x + 7) / 6) && ProbPrime((x + 1) / 24))) {
                        print("\r{},{:64}\n", x, ' ');
                    }
                }
            }
            // if (!ProbPrime(val) || !ProbPrime(val + 2) || !ProbPrime)
            return;
        }
        int p = primes[depth];

        long mul = inv[p][lcm % p];
        for (int i = 1; i <= rems[depth][0]; ++i) {
            int rem = rems[depth][i];
            long new_lcm = lcm * p, new_val = val + lcm * (((rem - val) % p + p) * mul % p);
            // print("{} {}\n", new_val % p, rem);
            dfs(depth + 1, new_lcm, new_val);
        }
    }

    void main() {
        PrimeSeq gen;
        for (int u; (u = gen.next()) < 100; )
            primes[++primes[0]] = u;
        for (int i = 1; i < 100; ++i) {
            inv[i][1] = 1;
            for (int j = 2; j < i; ++j)
                inv[i][j] = (i / j) * (i - inv[i][i % j]) % i;
        }

        total = 1;
        for (int i = 3; i <= PRIMES; ++i) {
            int p = primes[i];
            for (int t = 0; t < p; ++t) {
                bool ok = true;
                for (int j = 0; j < 9; ++j) {
                    if (j != 4 && (t + j) % p == 0) {
                        ok = false;
                    }
                }
                if (ok) {
                    rems[i][++rems[i][0]] = t;
                    // print("{} {}\n", p, t);
                }
            }
            total *= rems[i][0];
        }
        // rems[1][0] = 2, rems[1][1] = 1, rems[1][2] = 7;

        // dfs(4, 30, 11);
        print("total: {}\n", total);
        step = total / 10000;
        // dfs(3, 72, 47);
        dfs(3, 72, 41);
    }
}

int main() {
    PE526::main();
    return 0;
}