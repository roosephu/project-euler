#include <NTL/lzz_p.h>
#include <NTL/mat_lzz_p.h>
#include <NTL/lzz_pX.h>
#include "fmt/format.h"
using namespace NTL;
using namespace fmt;
using namespace std;

const int MOD = 1e9 + 7;

// const int n = 13, m = 10, N = n + 10;
// zz_p f[N][2], g[N][2], t[N][2][2];

// zz_p solve(int w, int h) {
//     for (int j = 0; j <= h; ++j)
//         f[j][0] = f[j][1] = 0;
//     for (int j = 1; j <= h; ++j)
//         f[j][j & 1] = 1;
//     for (int i = 2; i <= w; ++i) {
//         for (int j = 1; j <= h; ++j) {
//             t[j][0][0] = t[j - 1][0][0] + f[j][0];
//             t[j][0][1] = t[j - 1][0][1] + f[j][1];
//             t[j][1][0] = t[j - 1][1][1] + f[j][0];
//             t[j][1][1] = t[j - 1][1][0] + f[j][1];
//         }

//         for (int j = 1; j <= h; ++j) {
//             // int k = h - (h - j) % 2;
//             f[j][0] = t[h][0][0] - t[j][0][0] + t[j][1][0];
//             f[j][1] = t[h][0][1] - t[j][0][1] + t[j][1][1];
//             // print("w = {}, h = {}, f[{}, {}] = ({}, {})\n", w, h, i, j, rep(f[j][0]), rep(f[j][1]));
//         }
//         print("{},{},{},{} {},{},{},{}\n", rep(f[1][0]), rep(f[2][0]), rep(f[3][0]), rep(f[4][0]), rep(f[1][1]), rep(f[2][1]), rep(f[3][1]), rep(f[4][1]));
//     }

//     zz_p ans(0);
//     for (int i = 1; i <= h; ++i)
//         ans += f[i][0];
//     return ans;
// }

// const long n = 1e12, m = 100;
// zz_p solve(long w, long h) {
//     Mat<zz_p> U;
//     U.SetDims(2 * h, 2 * h);
//     for (int i = 1; i <= h; ++i) {
//         for (int j = 1; j <= h; ++j) {
//             for (int x = 0; x < 2; ++x) {
//                 int y = (x + max(j - i, 0)) % 2;
//                 U[2 * (i - 1) + x][2 * (j - 1) + y] += 1;
//                 // print("{} -> {}\n", 2 * (i - 1) + x, 2 * (j - 1) + y);
//             }
//         }
//     }

//     U = power(U, w - 1);
//     Vec<zz_p> x;
//     x.SetLength(2 * h);
//     for (int i = 1; i <= h; ++i)
//         x[2 * (i - 1) + (i % 2)] += 1;
//     x = x * U;

//     zz_p ans(0);
//     for (int i = 1; i <= h; ++i)
//         ans += x[2 * (i - 1)];
//     return ans;
// }

const long n = 100, m = 1e12, N = n + 10;

zz_p bernoulli[N], fac[N + 1], caf[N + 1];
zz_pX units[N];

zz_p cb(int n, int m) {
    return fac[n] * caf[m] * caf[n - m];
}

zz_pX acc(zz_pX f) {
    zz_pX ret;
    for (int i = 0; i <= deg(f); ++i) {
        ret += coeff(f, i) * units[i];
    }
    return ret;
}

zz_p solve(long w, long h) {
    fac[0] = 1;
    for (int i = 1; i <= N; ++i)
        fac[i] = fac[i - 1] * i;
    caf[N] = 1 / fac[N];
    for (int i = N; i >= 1; --i)
        caf[i - 1] = caf[i] * i;
    for (int i = 0; i < N; ++i) {
        zz_p s(i + 1);
        for (int j = 0; j < i; ++j) {
            zz_p coef = cb(i + 1, j) * bernoulli[j];
            s -= coef;
            SetCoeff(units[i], i + 1 - j, coef);
        }
        bernoulli[i] = s / (i + 1);
        SetCoeff(units[i], 1, s);
        units[i] /= i + 1;
        // print("unit {}: {}\n", i, rep(eval(units[i], zz_p(6))));
    }

    zz_pX f0, f1, g0, g1, minus, mod_pX;
    SetCoeff(f1, 0, 1);
    SetCoeff(g0, 0, 1);

    SetCoeff(minus, 0, -1);
    SetCoeff(minus, 1, 1);
    SetCoeff(mod_pX, N, 1);

    zz_p maxEven(h / 2), maxOdd(h - maxEven);
    zz_pXModulus mod(mod_pX);

    cout << f0 << " " << f1 << " " << g0 << " " <<  g1 << endl;

    for (int i = 1; i < w; ++i) {

        auto F0 = acc(f0), F0_comp = CompMod(F0, minus, mod);
        auto F1 = acc(f1), F1_comp = CompMod(F1, minus, mod);
        auto G0 = acc(g0), G0_comp = CompMod(G0, minus, mod);
        auto G1 = acc(g1), G1_comp = CompMod(G1, minus, mod);

        f0 = eval(F0, maxOdd) + eval(F1, maxEven) - F1_comp + G1_comp;
        f1 = eval(F0, maxOdd) + eval(F1, maxEven) - F0      + G0     ;
        g0 = eval(G0, maxOdd) + eval(G1, maxEven) - G1_comp + F1_comp;
        g1 = eval(G0, maxOdd) + eval(G1, maxEven) - G0      + F0     ;

        // cout << f0 << " " << f1 << " " << g0 << " " << g1 << endl;
        // cout << eval(f0, zz_p(1)) << "," << eval(f1, zz_p(1)) << "," << eval(f0, zz_p(2)) << "," << eval(f1, zz_p(2)) << " "
        //      << eval(g0, zz_p(1)) << "," << eval(g1, zz_p(1)) << "," << eval(g0, zz_p(2)) << "," << eval(g1, zz_p(2)) << " "
        //      << "|" << eval(F0, maxOdd) << "," << eval(F1, maxEven) << "(" << maxOdd << "," << maxEven << ")"
        //      << endl;
    }

    return eval(acc(f0), maxOdd) + eval(acc(f1), maxEven);
}

int main() {
    zz_p::init(MOD);

    zz_p ans1 = solve(n, m), ans2 = solve(n, m - 1);
    print("ans1 = {}, ans2 = {}, ans = {}\n", rep(ans1), rep(ans2), rep(ans1 - ans2));

    // F(1e4, 1e4)  = 749784357
    // F(1e12, 1e2) = 364553235
    // F(1e2, 1e12) = 635147632
    print("total ans = {}\n", rep(zz_p(749784357) + 364553235 + 635147632));
    return 0;
}
