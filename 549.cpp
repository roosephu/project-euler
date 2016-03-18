#include <cstdio>
#include <algorithm>
using namespace std;

const int n = 1e8, N = n + 10;

int primes[N], f[N];

int test(int n, int p) {
  int ret = 0;
  for (; n /= p; )
    ret += n;
  return ret;
}

int main() {
  for (int i = 2; i <= n; ++i) {
    if (!primes[i]) {
      primes[++primes[0]] = i;
      f[i] = i;
    }

    for (int j = 1, k = n / i; primes[j] <= k; ++j) {
      int p = primes[j], t = i * p;
      primes[t] = true;
      if (i % p == 0) {
        f[t] = f[i];
        int e = 1;
        for (int a = i; a % p == 0; a /= p)
          ++e;

        while (test(f[t], p) < e)
          f[t] = (f[t] / p + 1) * p;
        break;
      } else {
        f[t] = max(f[i], p);
      }
    }
  }

  long ans = 0;
  for (int i = 2; i <= n; ++i)
    ans += f[i];
  printf("%ld\n", ans);
  return 0;
}
