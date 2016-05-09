#include <cstdio>
using namespace std;

const long L = 1e8;

long ans = 0;

void dfs(long x1, long y1, long x2, long y2) {
    if (x1 * 100 >= y1 || y1 * y2 * 2 > L || (x1 == 0 && 2 * y2 * y2 >= L))
        return;
    if (x1 != 0 && (x1 * y2 + x2 * y1) * 50 < y1 * y2) {
        // printf("%ld %ld %ld %ld %ld %ld\n", x1, y1, x2, y2, x1 * y2 + x2 * y1, y1 * y2 * 2);
        ans += 1;
    }
    long u = x1 + x2;
    long v = y1 + y2;
    dfs(x1, y1, u, v);
    dfs(u, v, x2, y2);
}

int main() {
    dfs(0, 1, 1, 1);
    printf("%ld\n", ans + (L / 2 - 50));
    return 0;
}
