#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;

const int n = 10000000;

int f[n + 10], g[n + 10], h[n + 10];

int main() {
  for (int a = 2; a * a <= n; ++a)
    for (long long p = a * a; p <= n; p *= a) {
      int s = 0;
      for (int q = p; ; ) {
        s += q;
        if (q % a != 0)
          break;
        q = q / a * (a - 1);
      }
      for (int c = 1; c * p <= n; ++c)
        if (c * s > f[c * p]) {
          f[c * p] = c * s;
          g[c * p] = p;
          h[c * p] = a;
        }
    }
  int mx = 0;
  for (int i = 4; i <= n; ++i) {
    if (f[i] > mx) {
      mx = f[i];
      printf("%d: %d using %d^%d\n", i, f[i], h[i], (int)(log(g[i]) / log(h[i]) + 0.1));
    }
  }
  return 0;
}
