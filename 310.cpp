#include <cstdio>
using namespace std;

const int n = 1e5, N = n + 10, M = 128;

int f[N], t[M];
int x[M], y[M];

int main() {
  int mx = 0;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j * j <= i; ++j)
      t[f[i - j * j]] = i;
    for (; t[f[i]] == i; )
      ++f[i];
    if (f[i] > mx)
      mx = f[i];
  }
  for (int i = 0; i <= n; ++i)
    ++y[f[i]];

  printf("%d\n", mx);
  long long ans = 0;
  for (int b = 0; b <= n; ++b) {
    ++x[f[b]];
    for (int fa = 0; fa <= mx; ++fa)
      ans += 1ll * x[fa] * y[fa ^ f[b]];
    --y[f[b]];
  }
  printf("%lld\n", ans);

  return 0;
}
