#include "fmt/format.h"
#include <NTL/ZZ.h>
#include "fmt/ostream.h"
#include <vector>
#include <map>
using namespace fmt;
using namespace NTL;
using namespace std;

const long LMT = 50000;
const long TOTAL = LMT * LMT * 4;
const int LENGTH = 1e6;

long cnt1[LENGTH + 10], cnt2[LENGTH * 2 + 10];
long total = 0;

int run(long *cnt, long L, long R, int delta) {
    int t = 0;
    for (long a = 1, b_lb = SqrRoot(L); 2 * a * a <= R; ++a) {
        b_lb++;
        while (a * a + b_lb * b_lb >= L && b_lb >= a)
            --b_lb;
        // print("a = {}, b_lb = {}\n", a, b_lb);
        for (long b = b_lb + 1 + (((b_lb + 1) & delta) != (a & delta)); a * a + b * b <= R; b += delta + 1) {
            // if (delta && b >= a * 2) break;
            // if (L == 201)
                // print("{} {}\n", a, b);
            long s = a * a + b * b - L + 1;
            cnt[t] = s << 40 | a << 20 | b;
            ++t;
        }
    }
    sort(cnt, cnt + t);
    return t;
}

int main() {
    long ans = 0;
    for (long i = 1, step = max(1, TOTAL / LENGTH / 1000); i <= TOTAL / LENGTH; ++i) {
        long L = (i - 1) * LENGTH, R = i * LENGTH;
        int x = run(cnt1, L     + 1, R    , 0);
        int y = run(cnt2, L + L + 1, R + R, 1);
        // for (int t = 0; t < x; ++t) {
        //     print("{} ", cnt1[t] >> 40);
        // }
        // print("| ");
        // for (int t = 0; t < y; ++t) {
        //     print("{} ", cnt2[t] >> 41);
        // }
        // print("\n");

        for (int a = 0, b = 0; a < x && b < y; ) {
            int val = min(cnt1[a] >> 40, cnt2[b] >> 41);
            int A = a, B = b;
            while (A < x && (cnt1[A] >> 40) == val)
                ++A;
            while (B < y && (cnt2[B] >> 41) == val)
                ++B;
            for (int u = a; u < A; ++u) {
                for (int v = b; v < B; ++v) {
                    int _c = cnt1[u] >> 20 & 0xFFFFF, _t = cnt1[u] & 0xFFFFF;
                    int _a = cnt2[v] >> 20 & 0xFFFFF, _b = cnt2[v] & 0xFFFFF;

                    // if (_a * _a + _b * _b != L * 2 + val * 2)
                    //     print("b {} {} {}\n", _a, _b, val);
                    // // assert(_a * _a + _b * _b == L * 2 + v * 2);
                    // if (_c * _c + _t * _t != L + val)
                    //     print("a {} {} {}\n", _c, _t, val);
                    if (_c <= LMT && _b <= _c * 2 && _c * 2 < _a + _b) {
                        // print("{} {} {} {}\n", _a, _b, _c, _t);
                        ++ans;
                    }
                    if (_t <= LMT && _b <= _t * 2 && _t * 2 < _a + _b && _c != _t) {
                        // print("{} {} {} {}\n", _a, _b, _t, _c);
                        ++ans;
                    }
                }
            }

            a = A, b = B;
        }
        if (i % step == 0) {
            print("{}: {}, avg = {}, total = {}\n", i, 1. * clock() / CLOCKS_PER_SEC, 1. * clock() / CLOCKS_PER_SEC / (i / step), total);
        }
    }
    print("ans = {}\n", ans);

    // vector<pair<int, int>> tmp[12000];
    // for (int i = 1; i <= 50; ++i)
    //     for (int j = 1; j <= i; ++j)
    //         tmp[i * i + j * j].push_back({i, j});
    // for (int i = 2; i <= 10000; i += 2) {
    //     for (auto a : tmp[i]) {
    //         for (auto b : tmp[i / 2]) {
    //             if (a.first + a.second > b.first * 2)
    //                 print("({}, {}) ({}, {})\n", a.first, a.second, b.first, b.second);
    //         }
    //     }
    // }
    return 0;
}