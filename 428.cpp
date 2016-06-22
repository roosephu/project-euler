#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

const long n = 1e9, N = 50000, maxInterval = 10000000;

// long gcd(long a, long b) {
//     return a ? gcd(b % a, a) : b;
// }

struct node {
    int p, e;
};

int primes[N + 10];
bool is_prime[N + 10];
// vector<int> factors[maxInterval + 10];
vector<node> factors[maxInterval + 10];
int rem[maxInterval + 10];

int get_e(long n, int p) {
    int ret = 0;
    while (n % p == 0) {
        ++ret;
        n /= p;
    }
    return ret;
}

void init(int L, int R) {
    for (int i = L; i <= R; ++i) {
        rem[i - L] = i;
        factors[i - L].clear();
    }
    for (int i = 1; i <= primes[0]; ++i) {
        int p = primes[i], l = (L - 1) / p + 1, r = R / p;
        for (int x = l; x <= r; ++x) {
            int t = x * p - L, e = 0;
            while (rem[t] % p == 0) {
                rem[t] /= p;
                ++e;
            }
            factors[t].push_back((node){p, e});
        }
    }
    for (int i = L; i <= R; ++i) {
        if (rem[i - L] != 1) {
            // printf("%d\n", i);
            factors[i - L].push_back((node){rem[i - L], 1});
        }
    }
}

long solve(long L, long R, long mul, bool has3) {
    int a2 = get_e(mul, 2), a3 = get_e(mul, 3);
    long ret = 0;
    for (int i = L; i <= R; ++i) {
        // printf("cur: %d\n", i);
        int e2 = get_e(i, 2) * 2 + a2, e3 = get_e(i, 3) * 2 + a3;
        if (e3 > 0 && !has3)
            continue;

        int prod = (e2 + 1) * (e3 + 1);

        int f = e2 / 2 + 1, g = (e2 + 1) / 2;
        for (node x : factors[i - L]) {
            int e = x.e * 2, p = x.p;
            if (p == 2 || p == 3)
                continue;

            prod *= e + 1;

            if (!has3) {
                if (p % 3 == 2) {
                    int nf = (e / 2 + 1) * f + (e + 1) / 2 * g;
                    int ng = (e / 2 + 1) * g + (e + 1) / 2 * f;
                    f = nf, g = ng;
                } else {
                    f *= e + 1;
                    g *= e + 1;
                }
            }
            // printf("  %d\n", p);
        }

        // printf("%d: prod = %d\n", i, prod);
        if (!has3) {
            // printf("f = %d, g = %d, f + g = %d, prod = %d\n", f, g, f + g, prod);
            ret += i % 3 == 2 ? f : g;
            // ret += f;
        } else
            ret += prod;
    }
    printf("[L = %ld, R = %ld, mul = %ld] completed\n", L, R, mul);

    return ret;
}

int main() {
    for (int i = 2; i <= N; ++i)
        if (!is_prime[i]) {
            primes[++primes[0]] = i;
            // if (i <= 100)
            //     printf("%d\n", i);
            for (int j = i; j <= N; j += i)
                is_prime[j] = true;
        }

    long ans1 = 0, ans2 = 0, ans3 = 0;
    for (long L = 1; L <= n; ) {
        int R = min(n, L + maxInterval - 1);
        init(L, R);
        ans1 += solve(L, R, 4, false); // + solve(L, R, 4, true);
        ans2 += solve(L, R, 2, true);
        ans3 += solve(L, R, 12, true);

        L = R + 1;
    }
    for (long L = 1; L <= n / 3; ) {
        int R = min(n / 3, L + maxInterval - 1);
        init(L, R);
        ans1 += solve(L, R, 4, true);

        L = R + 1;
    }
    printf("new: ans = %ld + %ld + %ld = %ld\n", ans1, ans2, ans3, ans1 + ans2 + ans3);

    // ans1 = n, ans2 = 0, ans3 = 0;
    // for (long b = 1; b <= n; ++b) {
    //     for (long a = 1; a <= b * 10; ++a) {
    //         // if (2 * b * b % a == 0 && a * a <= 2 * b * b) // sigma(2b^2)
    //         //     tmp += 2;
    //         // if (b % 3 != 0 && 4 * b * b % a == 0 && a < 2 * b && (a + b) % 3 == 0) {
    //         //     tmp += 2;
    //         //     // printf("%ld %ld %ld\n", );
    //         // }
    //         // if (b % 3 == 0 && 4 * (b / 3) * (b / 3) % a == 0 && a < 2 * (b / 3)) { // sigma(4(b/3)^2)
    //         //     tmp += 2;
    //         //     // printf("%ld %ld %ld\n", a + (b / 3), b, b / 3 + 4 * (b / 3) * (b / 3) / a);
    //         // }
    //         // if (12 * b * b % a == 0 && a * a <= 12 * b * b) // sigma(12b^2)
    //         //     tmp += 2;

    //         if (3 * a > b && b * (a + b) % (3 * a - b) == 0) {
    //             long c = b * (a + b) / (3 * a - b);
    //             if (a != b && a < c)
    //                 ans1 += 2;
    //             else if (a < c)
    //                 ans1 += 1;
    //             // printf("1: %ld %ld %ld, %d\n", a, b, c, a != b && a < c ? 2 : 1);
    //         }

    //         if (a > b && b * (a + b) % (a - b) == 0) {
    //             long c = b * (a + b) / (a - b);
    //             if (a < c) {
    //                 ans2 += 2;
    //                 // printf("2: %ld %ld %ld, %d\n", a, b, c, a < c ? 2 : 0);
    //             }
    //         }

    //         if (a > b * 3 && 3 * b * (a + b) % (a - b * 3) == 0) {
    //             long c = 3 * b * (a + b) / (a - b * 3);
    //             if (a < c) {
    //                 ans3 += 2;
    //                 // printf("3: %ld %ld %ld, %d\n", a, b, c, a < c ? 2 : 0);
    //             }
    //         }
    //     }
    // }
    // printf("ans = %ld + %ld + %ld = %ld\n", ans1, ans2, ans3, ans1 + ans2 + ans3);
    // 73344 + 120398 + 244364
    // printf("tmp = %ld\n", tmp);

    // long ans1 = n, ans2 = 0, ans3 = 0;
    // for (long v = 1; v <= N; ++v) {
    //     // if (v % 10000 == 0)
    //     //     printf("1. %ld\n", v);
    //     for (long u = v - 1; sqrt(2) * u >= v; --u) {
    //         if (gcd(u, v) != 1)
    //             continue;
    //         long g = gcd(2 * u, v); // <= 2
    //         ans2 += n * g / (v - u) / (2 * u - v) * 2;
    //         if (4 * u >= 3 * v && (2 * n + 1) / (v - u) <= (2 * u - v))
    //             u = min(u, 3 * v / 2 - u + 10);
    //     }
    // }
    // printf("ans = %ld + %ld + %ld = %ld\n", ans1, ans2, ans3, ans1 + ans2 + ans3);
    // for (long v = 1; v <= N; ++v)
    //     for (long u = v - 1; sqrt(4 / 3.) * u >= v; --u) {
    //         if (gcd(u, v) != 1)
    //             continue;
    //         int g = gcd(4 * u, 3 * v); // <= 12
    //         ans3 += n * g / (v - u) / (4 * u - 3 * v) * 2;
    //         if (8 * u >= 7 * v && (12 * n + 1) / (v - u) <= (4 * u - 3 * v))
    //             u = min(u, 7 * v / 4 - u + 10);
    //         // if (v > n && n * g / (v - u) / (4 * u - 3 * v) * 2 > 0)
    //         //     printf("2. %ld %ld\n", u, v);
    //     }
    // printf("ans = %ld + %ld + %ld = %ld\n", ans1, ans2, ans3, ans1 + ans2 + ans3);
    // for (long v = 1; v <= N; ++v)
    //     for (long u = v - 1; 2 * u > v; --u) {
    //         if (gcd(u, v) != 1)
    //             continue;
    //         long g = gcd(v - u, 4 * u - v) * gcd(4 * u, v); // <= 12
    //         ans1 += n * g / (v - u) / (4 * u - v) * 2;
    //         if (8 * u >= 5 * v && (12 * n + 1) / (v - u) <= (4 * u - v))
    //             u = min(u, 5 * v / 4 - u + 10);
    //         // if (v > n && n * g / (v - u) / (4 * u - v) * 2 > 0)
    //         //     printf("3. %ld %ld\n", u, v);
    //     }
    // printf("ans = %ld + %ld + %ld = %ld\n", ans1, ans2, ans3, ans1 + ans2 + ans3);

    return 0;
}
