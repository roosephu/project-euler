#include <cstdio>
using namespace std;

const int P = 7, MOD = 5764801; // 729 * 729;
// const int P = 7, MOD = 5764801;

long ans = 0;
long invs[MOD];

long phi(long x) {
    return x / P * (P - 1);
}

long fpm(long b, long e, long m) {
    long t = 1;
    for (; e; e >>= 1, b = b * b % m)
        e & 1 ? t = t * b % m : 0;
    return t;
}

long inv(long x, long m) {
    return fpm(x, phi(m) - 1, m);
}

void dfs(long cur, long s) {
    if (cur * P >= MOD)
        return;
    printf("%ld\n", cur);

    for (int i = 1; i < P; ++i) {
        long ns = s + invs[cur * P + i] * MOD;
        if (ns % MOD == 0) {
            dfs(cur * P + i, ns / P);
        }
    }
}

int main() {
    for (int i = 1; i < MOD; ++i)
        if (i % P != 0)
            invs[i] = inv(i, MOD);
    for (int i = 1; i < MOD; ++i)
        invs[i] += invs[i - 1];
    dfs(0, 0);
    return 0;
}
