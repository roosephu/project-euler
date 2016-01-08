#include <cstdio>
#include <cmath>
using namespace std;

const int MOD = 1000000007;
const int n_0 = 10000000, n_1 = 10010000;
const int N = n_1 + 10;

long long fac[N], caf[N];

bool is_prime(int n) {
  for (int i = 2; i * i <= n; ++i)
    if (n % i == 0)
      return false;
  return n != 1;
}

int C(int n, int m) {
  return (long long)fac[n] * caf[m] % MOD * caf[n - m] % MOD;
}

int solve(int n) {
  long long ret = 0;
  double sqrt_n = sqrt(n);
  for (int x = 0; x <= sqrt_n; ++x) {
    ret += C(n - x * sqrt_n + x, x);
  }
  return ret % MOD;
}

long long fpm(long long b, long long e, long long m) {
  long long t = 1;
  for (; e; e >>= 1, b = b * b % m)
    e & 1 ? t = t * b % m : 0;
  return t;
}

int main() {
  fac[0] = 1;
  for (int i = 1; i <= n_1; ++i)
    fac[i] = fac[i - 1] * i % MOD;
  caf[n_1] = fpm(fac[n_1], MOD - 2, MOD);
  for (int i = n_1; i >= 1; --i)
    caf[i - 1] = caf[i] * i % MOD;

  printf("%d\n", solve(90));

  long long ans = 0;
  for (int i = n_0; i <= n_1; ++i) {
    if (!is_prime(i)) continue;
    ans += solve(i);
  }
  printf("%lld\n", ans % MOD);

  return 0;
}
