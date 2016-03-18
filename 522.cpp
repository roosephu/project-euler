#include <cstdio>
using namespace std;

const int n = 12344321, N = n + 10, MOD = 135707531;

long fac[N], caf[N];

long fpm(long b, long e, long m) {
  long t = 1;
  for (; e; e >>= 1, b = b * b % m)
    e & 1 ? t = t * b % m : 0;
  return t;
}

long cb(int n, int m) {
  return fac[n] * caf[m] % MOD * caf[n - m] % MOD;
}

/*
For a component, if
1. it's a cycle of size < n, we need to rewire 1 floor;
2. it's a cycle of size n => we've finished!
3. otherwise, we need to rewire \sum (max(in_degree[i], out_degree[i]) - 1) floors.
*/

int main() {
  fac[0] = 1;
  for (int i = 1; i <= n; ++i)
    fac[i] = fac[i - 1] * i % MOD;
  caf[n] = fpm(fac[n], MOD - 2, MOD);
  for (int i = n; i >= 1; --i)
    caf[i - 1] = caf[i] * i % MOD;

  long ans = 0;
  for (int i = 2; i < n; ++i) {
    ans += (i - 1) * cb(n - 1, i) % MOD * fpm(n - 2, n - 1 - i, MOD) % MOD * (n - 1) % MOD * n % MOD;
  }
  for (int i = 2; i < n - 1; ++i)
    ans += cb(n, i) * fac[i - 1] % MOD * fpm(n - i - 1, n - i, MOD) % MOD;

  printf("ans = %ld\n", ans % MOD);

  return 0;
}
