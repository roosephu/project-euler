#include <cstdio>
#include <set>
using namespace std;

const int n = 1000000, N = n + 100, M = 1024;

// int f[N][N], g[N][N], h[N][N];
long w[N], f[N], g[N], ff[M], gg[M];
int o[N];

void compute(long *f, long *ff) {
    int mx = 0;
    for (int i = 0; i <= n; ++i)
        o[i] = -1;

    for (int x = 1; x <= n; ++x) {
        if (x % 100000 == 0)
            printf("x = %d\n", x);
        for (int i = 1; w[i] > 0 && w[i] <= x; ++i)
            o[f[x - 1] ^ f[x - w[i]]] = x;

        int t = 0;
        while (o[t] == x)
            t += 1;
        f[x] = f[x - 1] ^ t;

        for (int i = 1; w[i] > 0 && w[i] <= x; ++i) {
            int v = f[x] ^ f[x - w[i]];
            if (v > mx)
                printf("new mx = %d\n", v), mx = v;
            ++ff[f[x] ^ f[x - w[i]]];
        }
    }
}

long mul(long a, long b) {
    long ret = 0;
    for (long i = 0; a >> i; ++i)
        for (long j = 0; b >> j; ++j)
            if ((a >> i & 1) && (b >> j & 1)) {
                long t = 1l << (i ^ j);
                for (int x = 0; (i & j) >> x; ++x)
                    if ((i & j) >> x & 1) {
                        // printf("%ld %ld: x = %d, %d\n", a, b, x, t);
                        t = mul(t, 3 * (1 << ((1 << x) - 1)));
                    }
                ret ^= t;
            }
    return ret;
}

int main() {


    // set<int> S, T;
    // for (int i = 1; i <= n; ++i) {
    //     S.insert(i * (i + 1) / 2);
    //     T.insert(i * i);
    // }
    // for (int i = 0; i <= n; ++i)
    //     for (int j = 0; j <= n; ++j)
    //         h[i][j] = -1;

    for (long i = 1; i * i <= n; ++i)
        w[i] = i * i;
    compute(g, gg);
    for (long i = 1; i * (i + 1) / 2 <= n; ++i)
        w[i] = i * (i + 1) / 2;
    compute(f, ff);

    // for (int i = 0; i <= n; ++i)
    //     for (int j = 0; j <= n; ++j) {
    //         set<int> S;
    //         for (int a = 0; a < i; ++a)
    //             for (int b = 0; b < j; ++b)
    //                 S.insert(mul[a][b] ^ mul[a][j] ^ mul[i][b]);
    //         while (S.count(mul[i][j]) != 0)
    //             mul[i][j] += 1;
    //         // printf("%d %d: %d\n", i, j, mul[i][j]);
    //     }

    // for (int a = 1; a <= n; ++a)
    //     for (int b = 1; b <= n; ++b) {
    //         set<int> v;
    //         for (auto x : S) {
    //             if (x > a) break;
    //             for (auto y : T) {
    //                 if (y > b) break;
    //                 v.insert(g[a - x][b - y] ^ g[a - x][b] ^ g[a][b - y]);
    //             }
    //         }

    //         g[a][b] = g[a - 1][b] ^ g[a][b - 1] ^ g[a - 1][b - 1];
    //         int t = 0;
    //         while (v.count(g[a][b] ^ t) > 0)
    //             t += 1;
    //         f[a][b] = t;
    //         g[a][b] ^= t;
    //         // printf("%d ", g[a][b]);
    //         // if (b == n)
    //         //     printf("\n");

    //         int x = g[a][1], y = g[1][b];
    //         if (h[x][y] == -1) {
    //             h[x][y] = g[a][b];
    //             printf("%d x %d = %d\n", x, y, g[a][b]);
    //         } else {
    //             if (h[x][y] != g[a][b]) {
    //                 printf("xxx\n");
    //             }
    //         }
    //     }
    // for (int i = 0; i < 16; ++i) {
    //     for (int j = 0; j < 16; ++j)
    //         printf("%d %d = %ld\n", i, j, mul(i, j));
    // }

    long ans = 0;
    for (int a = 0; a < M; ++a) {
        for (int b = 0; b < M; ++b) {
            if (ff[a] && gg[b] && mul(a, b) == mul(f[n], g[n]))
                ans += (long) ff[a] * gg[b];
        }
    }
    // for (int a = 1; a <= n; ++a)
    //     for (int b = 1; b <= n; ++b)
    //         for (auto x : S)
    //             for (auto y : T)
    //                 if (x <= a && y <= b && (g[a][b] ^ g[a - x][b] ^ g[a][b - y] ^ g[a - x][b - y]) == g[n][n]) {
    //                     printf("%d %d %d %d\n", a, b, x, y);
    //                     ans += 1;
    //                 }
    printf("ans = %ld\n", ans);
    return 0;
}
