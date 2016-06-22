#include <cstdio>
using namespace std;

const int n = 100000000, N = n + 10;

int f[N], g[N], notp[N];

int gcd(int a, int b) {
    return a ? gcd(b % a, a) : b;
}

int main() {
    for (int i = 2; i <= n; ++i)
        f[i] = 1;
    for (int i = 2; i <= n; ++i)
        if (!notp[i]) {
            for (int j = i; j <= n; j += i) {
                notp[j] = true;
                f[j] *= 2;
            }
        }

    int mx = 0;
    for (int i = 1; i <= n; ++i) {

        int t;
        if (i % 4 == 0)
            t = f[i / 2];
        else if (i % 2 == 0)
            continue;
        else
            t = f[i];

        t /= 2;
        for (int j = i; j <= n; j += i)
            g[j] += t;

        if (g[i] > mx) {
            mx = g[i];
            printf("update: %d, %d\n", i, g[i]);
        }
    }

    // for (int i = 1; i <= 20; ++i)
    //     printf("%d: %d, %d\n", i, f[i], g[i]);
    for (int i = 1; i <= n; ++i)
        if (g[i] == 47547) {
            printf("found: %d\n", i);
            break;
        }
    // for (int a = 1; a <= n; ++a)
    //     for (int b = 1; b < a && a * b <= n; ++b)
    //         if (gcd(a, b) == 1) {
    //             if ((a + b) % 2 == 0)
    //                 f[a * b]++;
    //             if (2 * a * b <= n)
    //                 f[2 * a * b]++;
    //         }
    // for (int i = 1; i <= 20; ++i)
    //     printf("%d: %d\n", i, f[i]);
    // for (int i = 1; i <= n; ++i)
    //     for (int j = 2; i * j <= n; ++j)
    //         f[i * j] += f[i];
    // for (int i = 1; i <= n; ++i) {
    //     if (f[i] == 47547) {
    //         printf("ans = %d\n", i);
    //         break;
    //     }
    // }
    return 0;
}
