#include <cstdio>
using namespace std;

const long long n = 1e15, m = 4e7, N = m + 10;

int primes[N], phi[N];

long long solve(long long t) {
  long long ret = 0;
  for (long long i = 1, j = 2; i <= t; ) {
    j = t / (t / i) + 1;
    ret += (t / i) * (j - i);
    // printf("%lld %lld %lld\n", i, j, t);
    i = j;
  }
  return ret;
}

int main() {
  for (int i = 2; i <= m; ++i) {
    if (!primes[i]) primes[++primes[0]] = i, phi[i] = i - 1;
    for (int j = 1, k = m / i; primes[j] <= k; ++j) {
      int t = i * primes[j]; primes[t] = 1;
      if (i % primes[j]) phi[t] = phi[i] * (primes[j] - 1);
      else {phi[t] = phi[i] * primes[j]; break; }
    }
  }
  phi[1] = 1;

  long long ans = 0;
  for (long long i = 1; i <= n / i; ++i) {
    ans += phi[i] * solve(n / i / i);
  }
  printf("%lld\n", ans);
  return 0;
}
