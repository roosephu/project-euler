#include <cstdio>
using namespace std;

const int n = 1e8, N = n + 10;

long long f[N], g[N], h[N];

int gcd(int a, int b) {
  return a ? gcd(b % a, a) : b;
}

int main() {
  long long ans = 0;
  printf("stage 1.\n");
  for (int i = 1; i <= n; ++i)
    g[i] = i;
  for (int i = 1; i <= n; ++i)
    for (int j = 2; i * j <= n; ++j)
      g[i * j] += i;

  printf("stage 2.\n");
  for (int a = 1; a * a <= n; ++a)
    for (int b = 1; a * a + b * b <= n; ++b)
      if (gcd(a, b) == 1)
        f[a * a + b * b] += a * 2;
  printf("stage 3.\n");
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; i * j <= n; ++j)
      h[i * j] += f[i] * g[j];
    ans += h[i] + g[i];
    // printf("f[%d] = %lld\n", i, g[i]);
  }
  printf("%lld\n", ans);
  return 0;
}
