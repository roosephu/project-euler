#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <iostream>
using namespace std;

#define maxprime 1100000
#define maxfac 10490
#define min(i,j) ({int _ = (i), __ = (j); _ < __ ? _ : __;})
#define max(i,j) ({int _ = (i), __ = (j); _ > __ ? _ : __;})

typedef long long int64;

int prime[maxprime], miu[maxprime], lnk[maxprime], dvs[maxprime];
int64 aux[maxfac], top, tot, n;

int64 gcd(int64 a, int64 b) {
    int t;
    for (; b; t = b, b = a % b, a = t);
    return a;
}

void init() {
    int i, j, k, t;
    for (i = 2, miu[1] = 1; i < maxprime; ++i) {
        if (!prime[i]) prime[++prime[0]] = i, miu[i] = -1, lnk[i] = 1, dvs[i] = i;
        for (j = 1, k = (maxprime - 1) / i; prime[j] <= k; ++j) {
            prime[t = i * prime[j]] = 1, dvs[t] = prime[j];
            if (i % prime[j]) miu[t] = -miu[i], lnk[t] = i;
            else {miu[t] = 0, lnk[t] = lnk[i]; break;}
        }
    }
}

void dfs(int64 n, int d, int v) {
    if (n == 1) return (void)(aux[++top] = v, tot = d);
    dfs(lnk[n], d + 1, v);
    dfs(lnk[n], d + 1, v * dvs[n]);
}

int prepare(int k) {
    return top = 0, dfs(k, 1, 1), sqrt(1.0 * top * n / tot / k);
}

int64 calc(int64 v) {
    int64 ret = 0, i;
    for (i = 1; i <= top; ++i)
        ret = ret + miu[aux[i]] * (v / aux[i]);
    return ret;
}

int main() {

    int64 ans = 0;

    cin >> n;
    init();

    for (int64 i = 1; i * i < n; ++i) {
        int64 k = max(min(prepare(i), 2 * i - 1), i), p, px, q, qx, T = n / i;
        for (int64 j = i + 1; j <= k; ++j)
            if (gcd(i, j) == 1)
                ans += T / j;
        for (p = k + 1, px = calc(k); p < 2 * i && p <= T; p = q + 1, px = qx) {
            q = min(2 * i - 1, T / (T / p)), qx = calc(q);
            ans += (T / q) * (qx - px);
        }
    }

    cout << ans << endl;
    return 0;
}
