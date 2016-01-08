#include <cstdio>
using namespace std;

const int n = 200000, N = n + 10;

int f[N], g[N];

int solve(int x, int p) {
  int t = 0;
  for (; x /= p; )
    t += x;
  return t;
}

int main() {
  for (int i = 0; i <= n; ++i) {
    f[i] = solve(i, 2);
    g[i] = solve(i, 5);
  }

  long long ans = 0;
  for (int a = 0; a <= n; ++a) {
    if (a % 100 == 0)
      printf("%d\n", a);
    for (int b = 0; a + b <= n; ++b)
      ans += f[a] + f[b] + f[n - a - b] + 12 <= f[n] && g[a] + g[b] + g[n - a - b] + 12 <= g[n];
  }
  printf("%lld\n", ans);
  return 0;
}
