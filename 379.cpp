#include <cstdio>
using namespace std;

const int M = 1.1e7;
const long long N = 1e12;

int primes[M + 2], mu[M + 2];
long long ft[M + 2];

long long f(long long n) { // #(i, j) s.t. i*j <= n
  if (n <= M)
    return ft[n];
  // printf("%lld\n", n);
  long long ret = 0;
  for (long long i = 1, j; i <= n; ) {
    j = n / (n / i) + 1;
    ret += (j - i) * (n / i);
    // printf("%lld %lld\n", i, j);
    i = j;
  }
  return ret;
}

long long g(long long n) { // #(i, j, k) s.t. i*j*k <= n
  // printf("%lld\n", n);
  long long ret = 0;
  for (long long i = 1, j; i <= n; ) {
    j = n / (n / i) + 1;
    ret += (j - i) * f(n / i);
    i = j;
  }
  return ret;
}

int main() {
  for (int i = 2; i <= M; ++i) {
    if (!primes[i]) primes[++primes[0]] = i, mu[i] = -1;
    for (int j = 1, k = M / i; primes[j] <= k; ++j) {
      int t = i * primes[j]; primes[t] = 1;
      if (i % primes[j] != 0) mu[t] = -mu[i];
      else {mu[t] = 0; break; }
    }
    // if (i <= 100) {
    //   printf("%d %d\n", i, mu[i]);
    // }
  }
  for (int i = 1; i <= M; ++i)
    for (int j = 1; i * j <= M; ++j)
      ++ft[i * j];
  for (int i = 1; i <= M; ++i)
    ft[i] += ft[i - 1];

  mu[1] = 1;
  long long ans = 0;
  for (long long t = 1; t * t <= N; ++t)
    ans += g(N / t / t) * mu[t];
  // f(101);
  printf("%lld\n", (N + ans) / 2);
  return 0;
}
