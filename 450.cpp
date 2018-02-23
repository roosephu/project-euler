#include "fmt/format.h"
#include <NTL/ZZ.h>
#include <tuple>
#include <set>
using namespace fmt;
using namespace NTL;
using namespace std;

namespace PE450 {
    const long maxN = 1e6, maxSqrtN = 1e3, N = maxN + 10;

    long ans = 0;
    int primes[N], mu[N];

    tuple<long, long, long> power_angle(long a, long b, long c, long e) {
        long x = 1, y = 0, z = 1;
        for (; e--; ) {
            long xx = x * a - y * b;
            long yy = x * b + y * a;
            x = xx;
            y = yy;
            z = z * c;
        }
        return {x, y, z};
    }

    void expand(long a, long b, long c) {
        for (int RR = 3; ; ++RR) {
            long cc = power_long(c, RR);
            if (cc > maxN * maxN / 2) break;
            for (int rr = 1; 2 * rr < RR; ++rr) {
                if (GCD(RR, rr) != 1) continue;
                auto [x1, y1, z1] = power_angle(a, b, c, rr);
                auto [x2, y2, z2] = power_angle(a, b, c, RR - rr);
                long xu = (RR - rr) * x1 * (z2 / z1) + rr * x2;
                long yu = (RR - rr) * y1 * (z2 / z1) - rr * y2;
                long gg = GCD(z2, GCD(xu, yu)), g = z2 / gg;
                long x = xu / gg, y = yu / gg;
                // print("x1 = {}, y1 = {}, z1 = {}, x2 = {}, y2 = {}, z2 = {}, g = {}, xu = {}, yu = {}\n", x1, y1, z1, x2, y2, z2, g, xu, yu);
                for (int i = 1; i * g * RR <= maxN; ++i) {
                    // if (RR * g * i != 2500 || rr * g * i != 1000) continue;
                    // print("x = {}, y = {}, R = {}, r = {}\n", x * i, y * i, RR * g * i, rr * g * i);
                    ans += (abs(x) + abs(y)) * i * 2;
                }
            }
            if (c == 1) break;
        }
    }

    void main() {
        // expand(1, 0, 1);
        // expand(-1, 0, 1);
        // expand(0, 1, 1);
        // expand(0, -1, 1);
        for (int u = 1; u * u <= maxSqrtN; ++u) {
            for (int v = 1; v <= u && u * u + v * v <= maxSqrtN; ++v) {
                if (GCD(u, v) == 1 && (u % 2) != (v % 2)) {
                    long a = u * u - v * v;
                    long b = 2 * u * v;
                    long c = u * u + v * v;
                    // print("a = {}, b = {}, c = {}\n", a, b, c);

                    // (a, b, c) = primitive
                    expand(a, b, c);
                    expand(-a, b, c);
                    // expand(-a, -b, c);
                    // expand(a, -b, c);
                    expand(b, a, c);
                    expand(-b, a, c);
                    // expand(-b, -a, c);
                    // expand(b, -a, c);
                }
            }
        }

        const int xc[4] = {1, 0, -1, 0}, xs[4] = {0, 1, 0, -1};
        // for (int R = 1; R <= maxN; ++R) {
        //     for (int r = 1; 2 * r < R; ++r) {
        //         long T = 0;
        //         int g = GCD(R, r), RR = R / g, rr = r / g;
        //         set<pair<int, int>> S;
        //         for (int t = 0; t < 4; ++t) {
        //             long x = (R - r) * xc[rr * t % 4] + r * xc[(RR - rr) * t % 4];
        //             long y = (R - r) * xs[rr * t % 4] - r * xs[(RR - rr) * t % 4];
        //             T += abs(x) + abs(y);
        //             pair<int, int> s = {x, y};
        //             if (S.count(s) || (R == 2500 && r == 1000)) {
        //                 print("!!! {} {} {} {}\n", x, y, RR, rr);
        //             }
        //             S.insert(s);
        //         }
        //         // if (RR % 2 == 1)
        //         //     assert(T == 4 * R - 2 * r);
        //         // else if (RR % 4 == 0)
        //         //     assert(T == 4 * R);
        //         // else if (RR % 4 == 2)
        //         //     assert(T == 4 * R - 4 * r);
        //         // else
        //         //     print("R = {}, r = {}, T = {}, est = {}, RR = {}, rr = {}\n", R, r, T, 4 * R - 2 * r, RR, rr);
        //         assert(T == 4 * R - 2 * r * (1 - xc[RR % 4]));
        //         ans += T;
        //     }
        // }
        for (int R = 1; R <= maxN; ++R) {
            for (int r = 1; 2 * r < R; ++r) {
                ans += 4 * R - 2 * r;
            }
        }

        long d1 = 0, d2 = 0;
        // for (int R = 1; R <= maxN; ++R) {
        //     for (int r = 1; 2 * r < R; ++r) {
        //         int g = GCD(R, r);
        //         int RR = R / g;
        //         d1 += 2 * r * xc[RR % 4];
        //     }
        // }

        mu[1] = 1;
        for (int i = 2; i <= maxN; ++i) {
            if (!primes[i]) primes[++primes[0]] = i, mu[i] = -1;
            for (int j = 1, k = maxN / i, t; primes[j] <= k; ++j) {
                primes[t = i * primes[j]] = 1;
                if (i % primes[j]) mu[t] = -mu[i];
                else { mu[t] = 0; break; }
            }
        }

        for (int d = 1; d <= maxN; ++d) {
            // print("d = {}, mu = {}\n", d, mu[d]);
            for (int R = d; R <= maxN; R += d) {
                if (R < 3) continue;
                d2 += (long) xc[R % 4] * (maxN / R) * (maxN / R + 1) / 2 * mu[d] * (R / 2 / d) * (R / 2 / d + 1) * d;
            }
        }
        print("ans = {}, d1 = {}, d2 = {}\n", ans + d2, d1, d2);
    }
}

int main() {
    PE450::main();
    return 0;
}
