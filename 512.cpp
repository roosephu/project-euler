#include <cstdio>
using namespace std;

const int n = 1e2, N = n + 2;

int primes[N];
int phi[N];

int main() {
  for (int i = 2; i <= n; ++i) {
    if (i % 10000 == 0)
      printf("%d\n", i);
    if (!primes[i]) primes[++primes[0]] = i, phi[i] = i - 1;
    for (int j = 1, t = n / i; primes[j] <= t; ++j) {
      int k = i * primes[j];
      if (primes[k] == 1)
        while (1);
      primes[k] = 1;
      if (i % primes[j] == 0) {
        phi[k] = phi[i] * primes[j];
        break;
      } else {
        phi[k] = phi[i] * (primes[j] - 1);
      }
    }
  }

  long long ans = 1;
  for (int i = 1; i <= n; i += 2)
    ans += phi[i];
  printf("%lld\n", ans);
  return 0;
}
