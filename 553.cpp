#include <cstdio>
using namespace std;

const int MOD = 1000000007;
const int n = 10000, k = 10, N = n + 10;

long g[N], f[N], dp[k + 1][N];
long fac[N], caf[N];

long fpm(long b, long e, long m) {
  long t = 1;
  for (; e; e >>= 1, b = b * b % m)
    e & 1 ? t = b * t % m : 0;
  return t;
}

// int bf(int now, int res, int n) {
//   if (now == 0)
//     return res == ((1 << n) - 1);
//   int ret = 0;
//   ret += bf(now - 1, res      , n);
//   ret += bf(now - 1, res | now, n);
//   return ret;
// }

long cb(int n, int m) {
  return fac[n] * caf[m] % MOD * caf[n - m] % MOD;
}

int main() {
  // printf("%d\n", bf(3, 0, 2));
  // printf("%d\n", bf(7, 0, 3));
  // printf("%d\n", bf(15, 0, 4));

  fac[0] = 1;
  for (int i = 1; i <= n; ++i)
    fac[i] = fac[i - 1] * i % MOD;
  caf[n] = fpm(fac[n], MOD - 2, MOD);
  for (int i = n; i >= 1; --i)
    caf[i - 1] = caf[i] * i % MOD;

  printf("Stage 1...\n");
  g[0] = 0;
  for (int i = 1; i <= n; ++i) {
    g[i] = fpm(2, fpm(2, i, MOD - 1) - 1, MOD) - 1; // g[i] <- 2^{2^i - 1} - 1
    for (int j = 1; j < i; ++j) {
      g[i] += cb(i, j) * g[i - j] % MOD * (MOD - 1) % MOD;
    }
    g[i] %= MOD;

    // printf("g[%d] = %ld\n", i, g[i]);
  }

  printf("Stage 2...\n");
  f[0] = 0;
  for (int i = 1; i <= n; ++i) {
    f[i] = g[i];
    for (int j = 1; j < i; ++j) {
      f[i] += cb(i - 1, j - 1) * f[j] % MOD * g[i - j] % MOD * (MOD - 1) % MOD;
    }
    f[i] %= MOD;

    // printf("f[%d] = %ld\n", i, f[i]);
  }

  dp[0][0] = 1;
  for (int i = 0; i < k; ++i) {
    printf("Stage 3.%d...\n", i);
    for (int j = 0; j <= n; ++j) {
      for (int t = 1; j + t <= n; ++t) {
        (dp[i + 1][j + t] += dp[i][j] * cb(j + t - 1, j) % MOD * f[t] % MOD) %= MOD;
      }
    }
  }

  long ans = 0;
  for (int i = 1; i <= n; ++i) {
    ans += dp[k][i] * cb(n, i) % MOD;
  }
  ans %= MOD;
  printf("ans = %ld\n", ans);
  return 0;
}
