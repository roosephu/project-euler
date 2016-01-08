#include <cstdio>
using namespace std;

const long long n = 1e13, m = 1e12, d = 1e4;
// const long long n = 100, m = 10, d = 4;
const int MOD = 999999937, N = 1e6;

long long fac[N + 1], caf[N + 1];

long long fpm(long long b, long long e, long long m) {
  long long t = 1;
  for (; e; e >>= 1, b = b * b % m)
    e & 1 ? t = t * b % m : 0;
  return t;
}

long long cb(long long n, long long m) {
  if (n == 0 && m == 0) return 1;
  long long ret = cb(n / MOD, m / MOD);
  n %= MOD, m %= MOD;
  if (n < m) return 0;
  return ret * fac[n] % MOD * caf[m] % MOD * caf[n - m] % MOD;
}

int main() {
  fac[0] = 1;
  for (int i = 1; i <= N; ++i)
    fac[i] = fac[i - 1] * i % MOD;
  caf[N] = fpm(fac[N], MOD - 2, MOD);
  for (int i = N; i >= 1; --i)
    caf[i - 1] = caf[i] * i % MOD;

  long long ans = 0, k = (m - d - 1) / MOD, mx = m - d - 1;
  for (long long i = k * MOD; i <= mx; ++i) {
    ans += cb(n - d, i) * ((mx - i) % 2 == 1 ? MOD - 1 : 1) % MOD;
  }
  ans = ans % MOD * cb(n, d) % MOD;
  printf("%lld\n", ans);
  return 0;
}
