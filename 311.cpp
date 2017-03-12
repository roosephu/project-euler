#include "fmt/format.h"
#include <NTL/ZZ.h>
#include <cstdlib>
using namespace fmt;
using namespace NTL;
using namespace std;

const long TOTAL = (long) 1e10 / 2;
const long BLOCK = 1e6;

unsigned char cnt[BLOCK + 100];
long ans = 0;

void run(long L, long R) {
    memset(cnt, 0, sizeof(cnt));
    for (long a = 0, b_lb = SqrRoot(L); 2 * a * a <= R; ++a) {
        b_lb++;
        while (a * a + b_lb * b_lb >= L && b_lb > a)
            --b_lb;
        // print("a = {}, b_lb = {}\n", a, b_lb);
        for (long b = b_lb + 1 + (((b_lb + 1) & 1) != (a & 1)); a * a + b * b <= R; b += 2) {
            long s = a * a + b * b - L;
            cnt[s] += 1;
        }
    }
    for (int i = 0; i <= R - L; ++i) {
        long x = cnt[i];
        ans += x * (x - 1) * (x - 2) / 6;
    }
}

int main() {
    for (long i = 1, step = max(1, TOTAL / BLOCK / 100); i <= TOTAL / BLOCK; ++i) {
        long L = (i - 1) * BLOCK, R = i * BLOCK;
        run(L + 1, R);
        if (i % step == 0) {
            print("{}: {}, avg = {}\n", i, 1. * clock() / CLOCKS_PER_SEC, 1. * clock() / CLOCKS_PER_SEC / (i / step));
        }
    }
    // for (long u = 1; u * u <= LMT; ++u) {
    //     for (long v = 0; v < u && u * u + v * v <= LMT; ++v) {
    //         if ((u & 1) != (v & 1)) continue;
    //         long s = u * u + v * v;
    //         cnt[s] += 1;
    //     }
    // }
    // long ans = 0;
    // for (int i = 1; i <= LMT; ++i) {
    //     int a = cnt[i];
    //     ans += a * (a - 1) * (a - 2) / 6;
    // }
    print("ans = {}\n", ans);
    return 0;
}