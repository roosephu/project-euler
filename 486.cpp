#include "fmt/format.h"
#include <vector>
#include <NTL/ZZ.h>
using namespace fmt;
using namespace std;
using namespace NTL;

const int M = 72000000, start = 100;
const long N = (long)1e18 - start;

int f5[100], f6[100], fail[M];
int f[100], g[100];
int w[M];
int F[6] = {34, 32, 32, 32, 34, 36};

vector<int> findRecurrence(int MOD, int MX) {
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 2; ++j)
            for (int k = 0; k < 2; ++k) {
                f5[i * 17 + j * 10 + k * 4] = 1;
                f6[i * 33 + j * 18 + k * 12] = 1;
            }
    for (int i = 0; i < 32; ++i)
        if (!f5[i])
            f[i] = 1;
    long total = (1 << 5) % MOD;

    int *S = w + start, p = 0;
    fail[0] = -1;

    vector<int> V;
    long W = 0;
    for (int T = 5; T <= start + MX; ++T) {
        // if (T % 10000000 == 0)
            // print("T = {}\n", T);
        long s = 0;
        if (T <= 100) {
            for (int i = 0; i < 32; ++i)
                s += f[i];
            // w[T] = (MOD + w[T - 1] + total - s % MOD) % MOD;
            for (int i = 0; i < 32; ++i)
                g[i] = 0;
            for (int i = 0; i < 32; ++i) {
                if (f5[i]) continue;
                for (int j = 0; j < 2; ++j) {
                    int k = (i << 1 | j) & 31;
                    if (!f6[i << 1 | j] && !f5[k]) {
                        g[k] += f[i];
                    }
                }
            }
            for (int i = 0; i < 32; ++i)
                if (!f5[i])
                    f[i] = g[i] % MOD;
        } else
            s = F[T % 6];

        W = (MOD + W + total - s % MOD) % MOD;
        total = 2 * total % MOD;

        // if (T <= 200 && T >= 160)
            // print("s = {}\n", s);
        int x = T - start;
        if (x >= 1 && W == 0) {
            V.push_back(x);
            // print("find {}\n", T);
        }
        // if (x > 1) {
        //     while (p >= 0 && S[x] != S[p + 1]) {
        //         p = fail[p];
        //     }
        //     p += 1;
        //     fail[x] = p;
        //     if (x == 2 * p) {
        //         print("period = {}\n", p);
        //         break;
        //     }
        // }
    }
    return V;
}

int main() {
    auto x1 = findRecurrence(9, 54);
    print(".\n");
    auto x2 = findRecurrence(1997, 11958036);
    print(".\n");
    auto x3 = findRecurrence(4877, 71340756);
    print(".\n");
    // findRecurrence(87654321, 100000000);

    long ans = 0;
    for (int i = 0; i < 6; ++i) {
        print("{}\n", i);
        vector<int> y1, y2, y3;
        for (auto x : x1)
            if (x % 6 == i)
                y1.push_back(x);
        for (auto x : x2)
            if (x % 6 == i)
                y2.push_back(x);
        for (auto x : x3)
            if (x % 6 == i)
                y3.push_back(x);

        const long period = 639821496386412l;
        auto p4 = PrepMulModPrecon(479866122289809l, period);
        auto p27 = PrepMulModPrecon(23697092458756l, period);
        auto p996503 = PrepMulModPrecon(42845117830920l, period);
        auto p5945063 = PrepMulModPrecon(93413163806928l, period);
        for (auto b : y2)
            for (auto c : y3)
                if (b % 12 == c % 12)
                    for (auto a : y1) {
                        // if (a == 5 && b == 1979 && c == 2411)
                            // print("...\n");
                        long MOD4 = b % 4;
                        long MOD27 = a % 27;
                        long MOD996503 = b % 996503;
                        long MOD5945063 = c % 5945063;
                        long x =
                            MulModPrecon(MOD4, 479866122289809l, period, p4) +
                            MulModPrecon(MOD27, 23697092458756l, period, p27) +
                            MulModPrecon(MOD996503, 42845117830920l, period, p996503) +
                            MulModPrecon(MOD5945063, 93413163806928l, period, p5945063);
                        x %= period;

                        ans += (N + period - x) / period;
                        // if ((N + period - x) / period > 0)
                            // print("x = {}\n", x);
                    }
    }
    print("ans = {}\n", ans);
    return 0;
}