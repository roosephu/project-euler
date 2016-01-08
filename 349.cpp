#include <cstdio>
using namespace std;

bool G[100][100];

int main() {
  int dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1};

  int x = 0, y = 0, d = 0, cnt = 0;
  for (int t = 0; t <= 1000; ++t) {
    printf("%d %d %d %d %d\n", t, x, y, d, cnt);
    for (int i = -5; i <= 5; ++i) {
      for (int j = -5; j <= 5; ++j)
        printf("%c", G[i + 50][j + 50] ? 'x' : ' ');
      printf("\n");
    }
    int s = G[x + 50][y + 50];
    if (s) {
      d = (d + 1) % 4;
    } else {
      d = (d + 3) % 4;
    }

    G[x + 50][y + 50] = 1 - s;
    x += dx[d];
    y += dy[d];
    cnt = cnt - s + (1 - s);
  }
  return 0;
}
