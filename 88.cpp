#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int n = 12000, N = n + 10;

int best[N];

void dfs(int prod, int sum, int v) {
  best[prod - sum] = min(best[prod - sum], prod);
  for (; v <= n + 2; ++v) {
    int np = prod * v, ns = sum + v - 1;
    if (np - ns > n)
      break;
    dfs(np, ns, v);
  }
}

int main() {
  memset(best, 0x3f, sizeof(best));
  dfs(1, 0, 2);

  sort(best + 2, best + n + 1);
  long long ans = 0;
  for (int i = 2; i <= n; ++i)
    if (best[i] != best[i - 1])
      ans += best[i];
  printf("ans = %lld\n", ans);
  return 0;
}
