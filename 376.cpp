#include "fmt/format.h"
using namespace fmt;

const int n = 30, N = n + 6 + 10;

int a[30], b[30], c[30];
long cb[N][N];
long cnt = 0;
long ans = 0;

void dfs(int dep, int A, int B, int C, int sab, int sbc, int sca) {
    if (A == 0 && B == 0 && C == 0) {
        // ++dep;
        // a[dep] = b[dep] = c[dep] = 6;
        if (dep > n)
            return;
        // print("{} [", dep);
        // for (int i = 1; i <= dep; ++i)
        //     print("{},", a[i] - a[i - 1]);
        // print("] [");
        // for (int i = 1; i <= dep; ++i)
        //     print("{},", b[i] - b[i - 1]);
        // print("] [");
        // for (int i = 1; i <= dep; ++i)
        //     print("{},", c[i] - c[i - 1]);
        // print("]");
        cnt += 1;
        ans += cb[n][dep];
        return;
    }
    if (dep == n)
        return;
    ++dep;
    for (int i = 0; i <= A; ++i)
        for (int j = 0; j <= B; ++j)
            for (int k = 0; k <= C; ++k) {
                if (i == A && j == B && k == C)
                    continue;
                a[dep] = a[dep - 1] + A - i;
                b[dep] = b[dep - 1] + B - j;
                c[dep] = c[dep - 1] + C - k;
                if (sab + A * b[dep] < 18 && sbc + B * c[dep] < 18 && sca + C * a[dep] < 18)
                    dfs(dep, i, j, k, sab + (A - i) * b[dep], sbc + (B - j) * c[dep], sca + (C - k) * a[dep]);
            }
}

int main() {
    for (int i = 0; i < N; ++i)
        for (int j = 0; j <= i; ++j)
            cb[i][j] = j ? cb[i - 1][j - 1]  + cb[i - 1][j] : 1;
    dfs(0, 6, 6, 6, 0, 0, 0);
    // dfs(0, 0, 0, 0, 0, 0, 0);
    print("cnt = {}, ans = {}, {}\n", cnt, ans / 3, ans % 3);
    return 0;
}
