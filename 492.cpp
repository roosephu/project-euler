#include <cstdio>
using namespace std;

const int L = 1e9, R = L + 1e7;
const long long n = 1e15;

long MOD;
typedef long mat[2][2];

long long f(long long x, long long MOD) {
    // return (x * x % MOD * 6 + 10 * x + 3) % MOD;
    return (x * x - 2) % MOD;
}

long long fpm(long b, long e, long m) {
    long t = 1;
    for (; e; e >>= 1, b = b * b % m)
        e & 1 ? t = t * b % m : 0;
    return t;
}

bool is_prime(int x) {
    for (int i = 2; i * i <= x; ++i)
        if (x % i == 0)
            return false;
    return x != 1;
}

long long solve_bf(int MOD) {
    long long x = 11, y = 11, m = n - 1;
    for (int cnt = 0; m; ) {
        --m;
        x = f(x, MOD);
        y = f(y, MOD);
        y = f(y, MOD);
        ++cnt;

        if (x == y) {
            m %= cnt;
            printf("loop: %d\n", cnt);
        }
    }
    return (x + MOD - 5) * fpm(6, MOD - 2, MOD) % MOD;
}

long mul(long a, long b, long m) {
    long t = 0;
    for (; a; a >>= 1, b = (b + b) % m)
        a & 1 ? t = (t + b) % m : 0;
    return t;
}

void matmul(mat a, mat b, mat c, int MOD) {
    mat t = {{0}};
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 2; ++j)
            for (int k = 0; k < 2; ++k)
                t[i][k] += a[i][j] * b[j][k] % MOD;
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 2; ++j)
            c[i][j] = t[i][j] % MOD;
}

long solve(long n, long MOD) {
    mat U = {{11, MOD - 1}, {1, 0}};
    mat V = {{2}, {11}};

    long res = 1, b = 2, mod = MOD * MOD - 1;
    for (; n; n >>= 1, b = mul(b, b, mod))
        n & 1 ? res = mul(res, b, mod) : 1;

    for (; res; res >>= 1, matmul(U, U, U, MOD))
        res & 1 ? matmul(U, V, V, MOD), 0 : 0;

    long ans = (V[0][0] + MOD - 5) * fpm(6, MOD - 2, MOD) % MOD;
    return ans;
}

int main() {

    long lx = 0;
    long long ans = 0;
    for (int MOD = L; MOD <= R; ++MOD)
        if (is_prime(MOD)) {
            if (MOD > lx) {
                printf("find prime: %d\n", MOD);
                lx = MOD + 100000;
            }
            ans += solve(n - 1, MOD);
        }
    printf("%lld\n", ans);
    // printf("%ld\n", solve(100 - 1, 1000000007));
    return 0;
}
