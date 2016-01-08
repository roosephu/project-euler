#include <cstdio>
#include <cmath>
using namespace std;

const int n = 2e7 - 1, N = n + 10, MOD = 1e9;

int primes[N];
double f[N];

long long order(long long p, long long v) {
  if (p != 2)
    return v - v / p;
  if (v == 2) return 1;
  if (v == 4) return 2;
  return v / 4;
}

int main() {
  for (int i = 2; i <= n; ++i) {
    if (!primes[i]) primes[++primes[0]] = i;
    for (int j = 1, k = n / i; primes[j] <= k; ++j) {
      int t = i * primes[j]; primes[t] = 1;
      if (i % primes[j] == 0) break;
    }
  }

  for (int i = 1; i <= primes[0]; ++i) {
    long long p = primes[i];
    double l = log(p);
    for (long long pp = p, o; (o = order(p, pp)) <= n; pp *= p) {
      for (int j = 1; j * o <= n; ++j)
        f[j * o] += l;
    }
  }

  int cur_max = 0, cur_sec = 0;
  for (int i = 1; i <= n; ++i)
    if (f[i] > f[cur_max])
      cur_sec = cur_max, cur_max = i;
  printf("max = %.3lf, sec = %.3lf\n", f[cur_max], f[cur_sec]);

  long long ans = 1;
  for (int i = 1; i <= primes[0]; ++i) {
    long long p = primes[i];
    for (long long pp = p, o; cur_max % (o = order(p, pp)) == 0; pp *= p)
      ans = ans * p % MOD;
  }
  printf("ans = %lld\n", ans + 1);

  return 0;
}
