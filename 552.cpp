#include <cstdio>
#include <algorithm>
using namespace std;

#define fst first
#define snd second

const int n = 300000, N = n + 10;

int primes[N];
int multiplier[N];

/*
  x = a % b
  x = c % d

  b t = c - a % d
  t = (c - a) * b^-1 % d
 */

pair<long, long> calc(int n, long MOD) {
  long ret = 0, mul = 1;
  for (int i = 1; i <= n; ++i) {
    ret += mul * multiplier[i] % MOD;
    mul = mul * primes[i] % MOD;
  }
  return {ret % MOD, mul};
}

long fpm(long b, long e, long m) {
  long t = 1;
  for (; e; e >>= 1, b = b * b % m)
    e & 1 ? t = t * b % m : 0;
  return t;
}

long inv(long a, long m) {
  return fpm(a, m - 2, m);
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
    if (i % 1000 == 1)
      printf("%d\n", i);
    int p = primes[i];
    auto prev = calc(i - 1, p);
    multiplier[i] = (i - prev.fst + p) * inv(prev.snd, p) % p;
  }

  long ans = 0;
  for (int i = 1; i <= primes[0]; ++i) {
    if (i % 1000 == 1)
      printf("%d\n", i);
    int p = primes[i];
    long rem = 0, mul = 1;
    for (int j = 1; j < i; ++j) {
      rem += mul * multiplier[j] % p;
      mul = mul * primes[j] % p;
      if (rem % p == 0) {
        ans += p;
        break;
      }
    }
  }
  printf("ans = %ld\n", ans);
  return 0;
}
