#include "fmt/format.h"
using namespace fmt;

const int N = 15;

int popcnt[16], var[16];
long ans = 0;
long cb[N][N];

void dfs(int depth, int sum, long cnt, int rem) {
    if (depth == 0) {
        if (sum != 0)
            return;
        // for (int i = 1; i < 16; ++i)
        //     print("{} ", var[i]);
        // print("\n");
        bool ok = true;
        int hall[16] = {0};
        for (int i = 1; i < 16; ++i) {
            for (int j = 1; j < 16; ++j) {
                if (i & j) {
                    hall[j] += var[i];
                }
            }
        }
        for (int i = 0; i < 16; ++i)
            if (hall[i] < popcnt[i])
                ok = false;
        if (ok) {
            ans += cnt;
        }
        return;
    }
    for (int i = 0; sum >= 0; ++i) {
        var[depth] = i;
        dfs(depth - 1, sum, cnt * cb[rem][i], rem - i);
        sum -= popcnt[depth];
    }
}

int main() {
    for (int i = 1; i < 16; ++i)
        popcnt[i] = popcnt[i >> 1] + (i & 1);
    for (int i = 0; i < N; ++i)
        for (int j = 0; j <= i; ++j)
            cb[i][j] = j ? cb[i - 1][j - 1] + cb[i - 1][j] : 1;
    for (int i = 4; i <= 13; ++i)
        dfs(15, i, 1, 13);
    print("ans = {}\n", ans);
    return 0;
}