#include <cstdio>
using namespace std;

const int n = 500, N = n + 10;

long double f[N], g[N];

int main() {
  for (int i = n - 1; i >= 0; --i) {
    f[i] = (1 + (1 - (i + 1.) / n) * f[i + 1]                ) / (1 - (i + 1) / 2. / n);
    g[i] = (1 + (1 - (i + 1.) / n) * g[i + 1] + f[i] / 2. / n) / (1 - (i + 1) / 2. / n);
  }
  printf("%.10f\n", (double)g[0]);
  return 0;
}
