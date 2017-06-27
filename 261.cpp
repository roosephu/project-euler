#include "fmt/format.h"
#include "bitset.h"
#include <NTL/ZZ.h>
#include <vector>
#include <set>
using namespace fmt;
using namespace NTL;
using namespace std;

namespace PE261 {
    const long N = 1e10;

    // unsigned ok[N / 32 + 10];

    vector<long> generate(long u, long d) { // a solution to
        vector<long> ret;
        long v = SqrRoot((u * u - 1) / d);
        for (long x = u, y = v; x <= N; ) {
            long p = x * u + d * y * v;
            long q = x * v + y * u;
            ret.push_back((x - 1) >> 1);
            x = p;
            y = q;
        }
        return ret;
    }

    long core(long v) {
        for (long i = 2; i * i <= v; ++i) {
            while (v % (i * i) == 0) {
                v /= i * i;
            }
        }
        return v;
    }

    long Sqrt(long a, long d) {
        return SqrRoot(a / GCD(d, a)) * SqrRoot((a + 1) / GCD(d, a + 1));
    }

    void main() {
        long count = 0;
        set<long> S, ks;
        for (long u = 1; u * u <= N * 0.55; ++u) {
            long d = core(u) * core(u + 1);
            if (S.count(d)) {
                continue;
            }
            auto vec = generate(u * 2 + 1, d);
            // if (u % 100 == 0)
            //     print("{}\n", u);
            // print("d = {}:", d);
            // for (long x : vec) {
            //     print(" {}", x);
            // }
            // print("\n");
            for (auto a : vec) {
                for (auto b : vec) {
                    if (b > a) {
                        break;
                    }
                    long s = Sqrt(a, d) * Sqrt(b, d) * d;
                    long k = s + (a + 1) * b;
                    long m = b;
                    long n = s + a * (b + 1);
                    if (k > N) {
                        break;
                    }
                    // print("find1: u = {} v = {}, k = {} m = {} n = {}, left = {}, right = {}\n", a, b, k, m, n, k * k, m * (k + n) * (n + 1 + m - k));
                    ks.insert(k);
                }
            }
        }
        print("count = {}\n", ks.size());

        // set<long> ks2;
        // for (long u = 1; u <= N; ++u) {
        //     for (long v = 1; v <= u && u * v <= N; ++v) {
        //         long S = u * (u + 1) * v * (v + 1);
        //         long s = SqrRoot(S);
        //         if (s * s == S) {
        //             long k = s + (u + 1) * v;
        //             long m = v;
        //             long n = u + k - m;
        //             if (k <= N) {
        //                 count += 1;
        //                 // if (ks.count(k) == 0) {
        //                     // print("find2: u = {} v = {}, k = {} m = {} n = {}, left = {}, right = {}\n", u, v, k, m, n, k * k, m * (k + n) * (n + 1 + m - k));
        //                 // }
        //                 // setbit(ok, k);
        //             }
        //         }
        //     }
        // }

        long ans = 0;
        for (auto k : ks)
            ans += k;
        print("ans = {}\n", ans);
    }
}

int main() {
    PE261::main();
    return 0;
}