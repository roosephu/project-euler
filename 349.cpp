#include <cstdio>
using namespace std;

const int n = 500, period = 104;
const long long N = 1e18;

bool G[n * 2][n * 2];

int main() {
  int dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1};

  int x = 0, y = 0, d = 0, cnt = 0;

  long long num_period = (N - 11000) / period;
  long long ans = num_period * 12;

  for (int t = 0; t < N - period * num_period; ++t) {
    // printf("%d %d %d %d %d\n", t, x, y, d, cnt);
    // for (int i = -5; i <= 5; ++i) {
    //   for (int j = -5; j <= 5; ++j)
    //     printf("%c", G[i + 50][j + 50] ? 'x' : ' ');
    //   printf("\n");
    // }
    int s = G[x + n][y + n];
    if (s) {
      d = (d + 1) % 4;
    } else {
      d = (d + 3) % 4;
    }

    G[x + n][y + n] = 1 - s;
    x += dx[d];
    y += dy[d];
    cnt = cnt - s + (1 - s);

    // printf("%d", s);
    // if (t % period == 0)
    //   printf("%d\n", cnt);
  }
  printf("%lld\n", ans + cnt);
  return 0;
}
