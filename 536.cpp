#include <cstdio>
using namespace std;

const long long n = 1e12;
const int N = 1e + 10;

int primes[N + 10];
long long ans = 0;

long long gcd(long long a, long long b) {
  return a ? gcd(b % a, a) : b;
}

long long lcm(long long a, long long b) {
  long long g = gcd(a, b);
  return a / g * b;
}

void dfs(int dep, long long l, long long m) {
  if (l > n || m > n)
    return;
  if (dep > primes[0] || m > n / primes[dep]) {
    if ((m + 3) % l == 0) {
      printf("%lld\n", m);
      ans += m;
    }
    return;
  }
  dfs(dep + 1, l, m);

  int p = primes[dep];
  l = lcm(l, p - 1);
  if (l > n)
    return;

  dfs(dep + 1, l, m * p);
}

int main() {
  for (int i = 2; i <= N; ++i) {
    if (!primes[i]) primes[++primes[0]] = i;
    for (int j = 1, k = N / i; primes[j] <= k; ++j) {
      int t = i * primes[j]; primes[t] = 1;
      if (i % primes[j] == 0) break;
    }
  }

  ans += 2;
  dfs(2, 1, 1); // do not search prime 2
  printf("ans = %lld\n", ans);

  return 0;
}
