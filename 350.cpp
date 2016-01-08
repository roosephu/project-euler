#include <cstdio>
using namespace std;

const int n = 1e6, N = n + 10, MOD = 104060401;
const long long L = 1e6, R = 1e12, X = 1e18;

long long f[N];
int dvs[N];

long long fpm(long long b, long long e, long long m) {
  long long t = 1;
  for (; e; e >>= 1, b = b * b % m)
    e & 1 ? t = t * b % m : 0;
  return t;
}

int main() {
  for (int i = 1; i <= n; ++i)
    for (int j = 1; i * j <= n; ++j)
      ++dvs[i * j];
  for (int i = 1; i <= n; ++i) {
    (f[i] += fpm(dvs[i], X, MOD)) %= MOD;
    for (int j = 2; i * j <= n; ++j)
      (f[i * j] += MOD - dvs[j] * f[i] % MOD) %= MOD;
  }

  long long ans = 0;
  for (int i = 1; i <= n; ++i) {
    long long lo = L, hi = R / i;
    if (lo > hi) break;
    ans += (hi - lo + 1) % MOD * f[i] % MOD;
  }
  printf("%lld\n", ans % MOD);

  return 0;
}
