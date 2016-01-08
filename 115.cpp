#include <cstdio>
using namespace std;

const int n = 1000, m = 50, N = n + 10;

long long f[N], g[N];

int main() {
  f[0] = 1, g[0] = 0;
  for (int i = 1; ; ++i) {
    g[i] = 0;
    for (int j = i - m; j >= 0; --j)
      g[i] += f[j];
    f[i] = f[i - 1] + g[i - 1];
    long long ans = f[i] + g[i];
    if (ans >= 1e6) {
      printf("%d\n", i);
      break;
    }
  }
  return 0;
}
