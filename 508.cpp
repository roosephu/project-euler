#include <cstdio>
using namespace std;

const int L = 4;

int f(int x, int y) {
  int ret = 0;
  for (; x || y; ) {
    // printf("%d %d\n", x, y);
    if ((4 + x % 2 + y % 2) % 2 == 1) {
      --x;
      ret += 1;
    }
    int xx = (y - x) / 2, yy = -(y + x) / 2;
    x = xx;
    y = yy;
    printf("%d %d\n", x, y);
    return ret;
  }
  return ret;
}

int main() {
  int ans = 0;
  for (int i = -L; i <= L; ++i) {
    for (int j = -L; j <= L; ++j) {
      if ((i + j) % 2 == 0)
        ans += f(i, j);
    }
  }
  printf("%d\n", ans);
  return 0;
}
