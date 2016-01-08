#include <cstdio>
using namespace std;

const int n = 1e7, N = n + 10;

long long f[N];

int main() {
  for (long long i = 1; i <= n; ++i) {
    if (i % 2 == 0)
      f[i] = (24 + i * i) / 48;
    else
      f[i] = (24 + (i + 3) * (i + 3)) / 48;
  }
  for (int i = 1; i <= 10; ++i) {
    printf("%d: %lld\n", i, f[i]);
  }

  for (int i = 1; i <= n; ++i)
    for (int j = i + i; j <= n; j += i)
      f[j] -= f[i];

  long long ans = 0;
  for (int i = 1; i <= n; ++i)
    ans += f[i];

  printf("%lld\n", ans);
  return 0;
}
