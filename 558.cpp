#include <cstdio>
using namespace std;

const int B = 1000;

int f[B * 2], g[B * 2];

void dfs(int *f, int x) {
    if (x < 0 || x >= B * 2)
        printf("xxx\n");
    if (f[x + 2]) {
        --f[x + 2];
        dfs(f, x + 3);
    } else if (f[x - 2]) {
        --f[x - 2];
        dfs(f, x + 1);
    } else if (f[x - 1]) {
        --f[x - 1];
        dfs(f, x + 1);
        dfs(f, x - 4);
    } else if (f[x + 1]) {
        --f[x + 1];
        dfs(f, x + 2);
        dfs(f, x - 3);
    } else if (f[x]) {
        --f[x];
        dfs(f, x + 1);
        dfs(f, x - 2);
        dfs(f, x - 7);
    } else
        ++f[x];
}

int main() {
    int ans = 0;
    for (int i = 1; i <= 5000000; ++i) {
        if (i % 100000 == 0)
            printf("%d\n", i);
        dfs(f, B);
        if (i != 1)
            dfs(f, B);

        for (int t = 0; t < B * 2; ++t)
            if (f[t])
                dfs(g, t);

        for (int t = 0; t < B * 2; ++t) {
            if (g[t]) {
                ++ans;
                // printf("%d ", t - B);
            }
        }
        // printf("\n");
    }
    printf("%d\n", ans);
    return 0;
}
