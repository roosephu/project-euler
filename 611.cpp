#include "lib.h"

/*
Let $f(x)$ be a complete multiplicative function, i.e., $f(a) f(b) = f(ab)$ for all $a, b \in \mathbb{N}$.
Define $T(x) = \sum_{d \in P, d \geq 2}^x f(x)$.
Define $S(x, t) = \sum_{d \geq 2, lpf(d) \geq t, or d \in [t - 1] \cap P}^x f(x)$.
We have $T(x) = S(x, sqrt(x)), S(x, t + 1) = S(x, t) - f(t) (S(x / t, t) - T(t - 1))$
*/

namespace PE611 {
    const long n = 1e12, maxSqrtN = 1e6;

    int check(int n) {
        while (n % 2 == 0) {
            n /= 2;
        }
        int cnt = 1;
        for (int i = 2; i * i <= n; ++i) {
            if (n % i == 0) {
                int e = 0;
                for (; n % i == 0; ++e)
                    n /= i;
                if (i % 4 == 3 && e % 2 != 0)
                    return 0;
                if (i % 4 == 1)
                    cnt *= e + 1;
            }
        }
        if (n != 1) {
            if (n % 4 == 3)
                return 0;
            cnt *= 2;
        }
        return cnt % 4 == 2; // || cnt % 4 == 3;
    }

    int f[maxSqrtN + 10];

    void main() {
        vector<long> sum_of_chi, pi;
        function<int (long)> get_index;
        tie(sum_of_chi, ignore, get_index) = sum_of_prime_func(n,
            [](long x) -> long { return x % 2 ? x % 4 == 1 ? 1 : -1 : 0; },
            [](long x) -> long { return x >= 3 && (x % 4 == 0 || x % 4 == 3) ? -1 : 0; }
        );
        tie(pi, ignore, ignore) = sum_of_prime_func(n,
            [](long x) -> long { return 1; },
            [](long x) -> long { return x - 1; }
        );

        for (int i = 1; i <= maxSqrtN; ++i) {
            f[i] = 1;
        }
        PrimeSeq gen;
        for (int u; (u = gen.next()) < maxSqrtN; ) {
            if (u % 4 != 1) continue;
            for (int i = u; i <= maxSqrtN; i += u) {
                int e = 1;
                for (int j = i; j % u == 0; j /= u)
                    e += 2;
                f[i] = f[i] * e % 4;
            }
        }

        long ans = 0;
        for (long i = 1; i * i <= n; ++i) {
            if (f[i] == 3) {
                long t = i * i;
                // print("{} ", t);
                ans += 1 + (t * 2 <= n);
            }
        }
        auto query = [&](long x) {
            if (x <= 2) return 0l;
            int idx = get_index(x);
            if ((pi[idx] - 1 + sum_of_chi[idx]) % 2 != 0) {
                print("x = {}, pi = {}, sx = {}\n", x, pi[idx], sum_of_chi[idx]);
            }
            return (pi[idx] + sum_of_chi[idx] - 1) / 2;
        };
        for (long i = 1; i * i <= n; ++i) {
            long t = i * i;
            ans += query(n / t);
            ans += query(n / t / 2);
        }

        gen.reset(0);
        for (long u; (u = gen.next()) < maxSqrtN; ) {
            if (u % 4 != 1) continue;
            for (long i = u; i <= maxSqrtN && i * i * u <= n; i += u) {
                int e = 1;
                for (int j = i; j % u == 0; j /= u) {
                    e += 2;
                }
                int x = f[i] * e % 4;
                if (x * (e + 1) % 4 != 2) {
                    --ans;
                    if (i * i * u * 2 <= n) {
                        --ans;
                    }
                }
            }
        }
        // // print("\n");
        // for (int i = 1; i <= n; ++i) {
        //     if (check(i)) {
        //         ans += 1;
        //         // print("{} ", i);
        //     }
        // }
        // print("\n");
        print("ans = {}\n", ans);
    }
}

int main() {
    PE611::main();
    return 0;
}
