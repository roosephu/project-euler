#include <cstdio>
using namespace std;

const int n = 50;

long long f[100], g[100];

int main() {
  f[0] = 1, g[0] = 0;
  for (int i = 1; i <= n; ++i) {
    g[i] = 0;
    for (int j = i - 3; j >= 0; --j)
      g[i] += f[j];
    f[i] = f[i - 1] + g[i - 1];
  }
  printf("%lld\n", f[n] + g[n]);
  return 0;
}
