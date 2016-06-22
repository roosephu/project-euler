#include <cstdio>
#include <set>
using namespace std;

const int n = 1e7, k = 1e7, N = n + 10, M = 1048576, MOD = 1000000007;

int f[N];
long g[M], tmp[M];

long fpm(long b, long e, long m) {
    long t = 1;
    for (; e; e >>= 1, b = b * b % m)
        e & 1 ? t = t * b % m : 0;
    return t;
}

void fwt(long *g, int width, int n) {
    if (n == 1)
        return;
    fwt(g        , 2 * width, n / 2);
    fwt(g + width, 2 * width, n / 2);

    for (int i = 0; i < n / 2; ++i) {
        long u = g[i * width * 2], v = g[i * width * 2 + width];
        tmp[i        ] = (u + v) % MOD;
        tmp[i + n / 2] = (u + MOD - v) % MOD;
    }

    for (int i = 0; i < n; ++i) {
        g[width * i] = tmp[i];
    }
}

int main() {
    for (int i = 1; i <= n; ++i)
        f[i] = -1;
    f[1] = 1;

    int cnt = 0;
    for (int i = 2; i <= n; ++i)
        if (f[i] == -1) {
            ++cnt;
            f[i] = cnt == 1 ? 0 : cnt;
            for (int j = i; j <= n; j += i)
                if (f[j] == -1)
                    f[j] = f[i];
        }
    for (int i = 1; i < n; ++i)
        ++g[f[i]];

    printf("%d\n", cnt);
    fwt(g, 1, M);
    long coef = fpm(M, MOD - 2, MOD);
    for (int i = 0; i < M; ++i)
        g[i] = fpm(g[i], k, MOD) * coef % MOD;
    fwt(g, 1, M);
    printf("ans = %ld\n", g[0]);

    return 0;
}
