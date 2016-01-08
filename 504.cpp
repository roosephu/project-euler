#include <cstdio>
using namespace std;

const int m = 100, M = m + 1;

int gcd[M][M], is_sqr[M * M * 4];

int G(int i, int j) {
  return j ? G(j, i % j) : i;
}

int main() {
  for (int i = 0; i <= m; ++i)
    for (int j = 0; j <= m; ++j)
      gcd[i][j] = G(i, j);
  for (int i = 0; i <= m * 2; ++i)
    is_sqr[i * i] = true;

  int ans = 0;
  for (int a = 1; a <= m; ++a)
    for (int b = 1; b <= m; ++b)
      for (int c = 1; c <= m; ++c)
        for (int d = 1; d <= m; ++d) {
          int A = a * b + b * c + c * d + d * a;
          int B = gcd[a][b] + gcd[b][c] + gcd[c][d] + gcd[d][a];
          int inner = 1 + (A - B) / 2;
          ans += is_sqr[inner];
        }
  printf("%d\n", ans);
  return 0;
}
