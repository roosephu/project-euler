#include <cstdio>
using namespace std;

const int n = 1e7, N = n + 10;

bool primes[N];

int main() {
  for (int i = 2; i <= n; ++i)
    if (!primes[i])
      for (int j = 2; i * j <= n; ++j)
        primes[i * j] = true;
  long long ans = 0;
  for (int i = 2; i < n; ++i) {
    if (primes[i])
      continue;
    for (int k = 0; k < 10; ++k) {
      if (i * k % 10 == 9) {
        ans += (i * k + 1) / 10;
        break;
      }
    }
  }
  printf("%lld\n", ans);
  return 0;
}
