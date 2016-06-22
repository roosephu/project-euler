#include <cstdio>
#include <map>
using namespace std;

const int n = 14, N = 16;

map<long, long> f[N];
long hit[N];
int w;
long mask;

long dfs(int dep, long state) {
    if (dep == n)
        return 1;

    if (w > 7 || !f[dep].count(state)) {
        int invalid = 0;
        for (int i = 0; i < w; ++i) {
            int p = state >> (4 * i) & 15;
            if (p != 15) {
                invalid |= 1 << p;
                invalid |= 1 << (p + i + 1);
                if (p > i)
                    invalid |= 1 << (p - i - 1);
            }
        }
        long ret = 0;
        for (int i = 0; i < n; ++i)
            if ((invalid >> i & 1) == 0)
                ret += dfs(dep + 1, ((state << 4) | i) & mask);
        if (w > 7)
            return ret;
        f[dep][state] = ret;
    } else
        ++hit[dep];
    return f[dep][state];
}

int main() {
    long ans = 0;
    for (w = 0; w < n; ++w) {
        mask = (1l << (4 * w)) - 1;
        for (int i = 0; i <= n; ++i) {
            f[i].clear();
            hit[i] = 0;
        }
        ans += dfs(0, mask);
        for (int i = 0; i <= n; ++i) {
            printf("%d(%ld) ", (int) f[i].size(), hit[i]);
        }
        printf("\n");
    }
    printf("ans = %ld\n", ans);
    return 0;
}
