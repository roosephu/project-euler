#include <cstdio>
using namespace std;

const int M = 16, MOD = 1e9 + 7;

long long fac[M + 10], caf[M + 10];
long long limit[M];
long long f[1 << M];

long long fpm(long long b, long long e, long long m) {
  long long t = 1;
  for (; e; e >>= 1, b = b * b % m)
    e & 1 ? t = t * b % m : 0;
  return t;
}

long long C(long long n, int m) {
  if (n < 0)
    return 0;
  long long ret = 1;
  for (int i = 0; i < m; ++i)
    ret = ret * ((n - i) % MOD) % MOD;
  return ret * caf[m] % MOD;
}

long long solve(long long n, int k, int b) {
  limit[0] = 1;
  for (int i = 1; i <= k; ++i)
    limit[i] = limit[i - 1] * b;

  int mask = (1 << k) - 1;
  for (int S = 0; S <= mask; ++S) {
    long long total = n;
    for (int i = 0; i < k; ++i)
      if ((S >> i & 1) == 0)
        total -= limit[i + 1] + 1;
    f[S] = C(total + k, k);
    for (int T = S; T; T = (T - 1) & S)
      f[S] -= f[S ^ T];
    f[S] = (MOD + f[S] % MOD) % MOD;
    // printf("%d: %lld, %lld = %lld\n", S, total, choose, f[S]);
  }
  return f[mask];
}

int main() {
  fac[0] = 1;
  for (int i = 1; i <= M; ++i)
    fac[i] = fac[i - 1] * i % MOD;
  caf[M] = fpm(fac[M], MOD - 2, MOD);
  for (int i = M; i >= 1; --i)
    caf[i - 1] = caf[i] * i % MOD;

  long long ans = 0;
  for (int k = 10; k <= 15; ++k) {
    long long n = 1;
    for (int i = 1; i <= k; ++i)
      n *= 10;
    ans += solve(n, k, k);
  }
  printf("ans = %lld\n", ans % MOD);
  return 0;
}
