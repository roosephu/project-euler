#include <cstdio>
using namespace std;

const int n = 9, m = 12, N = 1 << (n * 2);

#define get(S, x) ((S) >> (x) & 1)
#define set(x) (1 << (x))

long long f[N], g[N];

void dfs(int d, int S, int T) {
  if (d < 0) {
    if (((T + 1) & ((1 << n) - 1)) == 0)
      g[T >> n] += f[S];
    return;
  }
  dfs(d - 1, S, T);
  if (!get(T, d) && !get(T, d + n))
    dfs(d - 1, S, T | set(d) | set(d + n) | set(d + 2 * n));
  if (d >= 2)
    dfs(d - 3, S, T | set(d + 2 * n) | set(d - 1 + 2 * n) | set(d - 2 + 2 * n));
  if (d >= 1 && !get(T, d + n) && !get(T, d + n * 2 - 1))
    dfs(d - 2, S, T | set(d + n) | set(d + n * 2 - 1) | set(d + n * 2));
  if (d >= 1 && !get(T, d + n - 1) && !get(T, d + n * 2 - 1))
    dfs(d - 2, S, T | set(d + n - 1) | set(d + n * 2 - 1) | set(d + n * 2));
  if (d >= 1 && !get(T, d + n - 1) && !get(T, d + n))
    dfs(d - 1, S, T | set(d + n - 1) | set(d + n) | set(d + n * 2));
  if (!get(T, d + n) && !get(T, d + n + 1) && d < n - 1)
    dfs(d - 1, S, T | set(d + n + 1) | set(d + n) | set(d + n * 2));
}

int main() {
  f[N - 1] = 1;
  for (int i = 1; i <= m; ++i) {
    printf("current: %d\n", i);
    for (int s = 0; s < N; ++s)
      if (f[s])
        dfs(n - 1, s, s);
    for (int s = 0; s < N; ++s)
      f[s] = g[s], g[s] = 0;
  }
  printf("%lld\n", f[N - 1]);
  return 0;
}
