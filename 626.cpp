#include "lib.h"
#include <ctime>

namespace PE626 {
    const int n = 20;
    const int MOD = 1001001011;

    vector<pair<vector<int>, long>> partitions;
    long factorial[n + 1];

    long power(long b, long e, long m) {
        long t = 1;
        for (; e; e >>= 1, b = b * b % m)
            e & 1 ? t = t * b % m : 0;
        return t;
    }

    long inv(long x) {
        return power(x, MOD - 2, MOD);
    }

    void dfs(vector<int> p, int rem, int last) {
        if (rem == 0) {
            long total = factorial[n];
            int cnt[n + 1] = {0};
            for (auto a : p) {
                cnt[a] += 1;
            }
            for (int i = 1; i <= n; ++i) {
                total = total * inv(factorial[cnt[i]]) % MOD * inv(power(i, cnt[i], MOD)) % MOD;
            }
            partitions.push_back({p, total});
            return;
        }
        last = min(rem, last);

        for (int i = last; i; --i) {
            auto q = p;
            q.push_back(i);
            dfs(q, rem - i, i);
        }
    }

    long countf(vector<int> pa, vector<int> pb) {
        long m = pa.size() + pb.size();
        long x[50] = {0};
        int n_sols = n * 2;
        int freedom = 0;
        for (int i = 0; i < pa.size(); ++i) {
            for (int j = 0; j < pb.size(); ++j) {
                int A = pa[i], B = pb[j];
                int g = GCD(A, B);
                int a = A / g, b = B / g;
                freedom += g;
                long y = 0;
                if (b % 2 == 1) {
                    y |= 1l << i;
                }
                if (a % 2 == 1) {
                    y |= 1l << (j + pa.size());
                }
                for (int t = 0; t < m; ++t) {
                    if (y >> t & 1) {
                        if (x[t]) {
                            y ^= x[t];
                        } else {
                            x[t] = y;
                            break;
                        }
                    }
                }
            }
        }
        for (int t = 0; t < m; ++t) {
            if (x[t] != 0) {
                n_sols -= 1;
            }
        }
        return power(2, freedom + n_sols - n * 2, MOD);
    }

    void main() {
        factorial[0] = 1;
        for (int i = 1; i <= n; ++i) {
            factorial[i] = factorial[i - 1] * i % MOD;
        }
        dfs({}, n, n);

        long ans = 0;
        double ta = clock();
        for (auto p : partitions) {
            for (auto q : partitions) {
                ans += countf(p.first, q.first) * p.second % MOD * q.second % MOD;
            }
        }
        double tb = clock();
        print("ans = {}\n", ans % MOD * power(inv(factorial[n]), 2, MOD) % MOD);
        print("{}\n", tb - ta);
    }
}

int main() {
    PE626::main();
    return 0;
}
