#include "fmt/format.h"
#include <NTL/ZZ.h>
using namespace fmt;
using namespace NTL;

// int a[8], b[8], U[8][8];

// int main() {
//     a[0] = 1;
//     U[0][1] = 6;
//     U[1][1] = 3;
//     U[1][2] = 2;
//     U[1][4] = 1;
//     U[2][1] = 1;
//     U[2][2] = 2;
//     U[2][3] = 1;
//     U[2][4] = 2;
//     U[3][3] = 3;
//     U[3][4] = 3;
//     U[4][5] = 6;
//     U[5][5] = 3;
//     U[5][6] = 2;
//     U[6][5] = 1;
//     U[6][6] = 2;
//     U[6][7] = 1;
//     U[7][7] = 3;

//     for (int i = 1; i <= 11; ++i) {
//         int A = 0, B = 0;
//         for (int x = 0; x < 4; ++x) {
//             A += a[x];
//             B += a[x + 4];
//         }
//         print("A = {}, B = {}, t = {}\n", A, B, a[4]);
//         for (int x = 0; x < 8; ++x)
//             b[x] = 0;
//         for (int x = 0; x < 8; ++x)
//             for (int y = 0; y < 8; ++y)
//                 b[y] += a[x] * U[x][y];
//         for (int x = 0; x < 8; ++x)
//             a[x] = b[x];
//     }
//     return 0;
// }

const int n = 1e7;

int main() {
    long ans = 0;
    for (long t = 1; t <= n - 2; ++t) {
        long v = 7 * t + 17;
        long A = GCD(v, (2 * PowerMod(4, t, v) - PowerMod(3, t, v)) % v + v);
        long B = GCD(v, ((3 * t - 17) * PowerMod(4, t, v) + (2 * t + 17) * PowerMod(3, t, v)) % v + v);
        ans += GCD(A, B) * 6;
    }
    print("ans = {}\n", ans);
    return 0;
}