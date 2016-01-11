#include <cstdio>
#include <algorithm>
using namespace std;

const int n = 100, N = n + 10;

double f[N][N], g[N][N];

double prob(int a, int b, double (*f)[N]) {
  if (a >= n)
    return 0;
  else if (b >= n)
    return 1;
  else
    return f[a][b];
}

int main() {
  for (int i = n - 1; i >= 0; --i)
    for (int j = n - 1; j >= 0; --j) {
      for (int _ = 0; _ < 200; ++_) {
        f[i][j] = (prob(i + 1, j, g) + g[i][j]) / 2;
        double mx = -1e300;
        for (int t = 1; t <= 8; ++t)
          mx = max((prob(i, j + (1 << (t - 1)), f) - f[i][j]) / (1 << t), mx);
        g[i][j] = mx + f[i][j];
      }
    }
  printf("%.8f\n", f[0][0]);

  return 0;
}
