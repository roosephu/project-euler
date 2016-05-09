#include <cstdio>
using namespace std;

const long n = (long)1e12 - 10, m = 1e18;

long f[1 << 19 | 100], g[10000];

long mul(long a, long b, long m) {
    long ret = a * b - (long)((long double)a * b / m) * m;
    while (ret < 0)
        ret += m;
    while (ret >= m)
        ret -= m;
    return ret;
}

long fpm(long b, long e, long m) {
    long t = 1;
    for (; e; e >>= 1, b = mul(b, b, m))
        e & 1 ? t = mul(t, b, m) : 0;
    return t;
}

long dfs(long *f, long n, int p, long pow, long acc) {
    if (n < pow) {
        f[++f[0]] = acc;
        if (f[0] % 10000 == 0)
            printf("p = %d, cnt = %ld, pow = %ld\n", p, f[0], pow);
        // if (p == 2)
        //     printf("p = %d, acc = %ld, cnt = %ld\n", p, acc, f[0]);
        return pow;
    }
    int x = n / pow % p; long ret = 0;
    for (; x < p; ++x)
        ret = dfs(f, n, p, pow * p, acc + x * pow);
    return ret;
}

int main() {
    long p2 = dfs(f, n, 2, 1, 0);
    long p5 = dfs(g, n, 5, 1, 0);

    long c2 = fpm(p2, p5 / 5 * 4 - 1, p5);
    long c5 = fpm(p5, p2 / 2 - 1, p2);
    // long M = p2 * p5;
    long ans = m - n;
    long limX = m / p5 + 100, limY = m / p2 + 100;

    printf("p2 = %ld, p5 = %ld\n", p2, p5);
    for (int i = 1; i <= f[0]; ++i)
        ans -= (m - f[i] + p2 - 1) / p2 - (n - f[i] + p2 - 1) / p2;
    for (int i = 1; i <= g[0]; ++i)
        ans -= (m - g[i] + p5 - 1) / p5 - (n - g[i] + p5 - 1) / p5;
    for (int j = 1; j <= g[0]; ++j) {
        printf("progress: %d/%d\n", j, g[0]);
        for (int i = 1; i <= f[0]; ++i) {
            // x % p2 = f[i], x % p5 = g[i]
            long x = mul(f[i], c5, p2), y = mul(g[j], c2, p5);
            // if ((p5 * x + p2 * y) % (p2 * p5) <= m)
            //     printf("f[i] = %ld, g[j] = %ld, x = %ld, y = %ld\n", f[i], g[j], x, y);

            if (x <= limX && y <= limY) {
                long v = p5 * x + p2 * y;
                ans += n <= v && v < m;
                // if (n <= v && v < m)
                //     printf("hit!\n");
            } else {
                long lb = -(long double)y * p2 / p5 + p2 - 10, rb = lb + limX + 10;
                // if ((p5 * x + p2 * y) % (p2 * p5) <= m)
                //     printf("lb = %ld, rb = %ld\n", lb, rb);
                if (lb <= x && x <= rb) {
                    long v = p5 * x + p2 * y - p2 * p5;
                    ans += n <= v && v < m;
                    // if (n <= v && v < m)
                    //     printf("hit!\n");
                }
            }
        }
    }
    printf("ans = %ld\n", ans);
    return 0;
}
