#include <cstdio>
#include <cmath>
using namespace std;

int main() {
  int cnt = 0;
  for (int m = 1; m <= 10000; ++m) {
    for (int i = 1; i <= m; ++i) {
      for (int j = i; j <= m; ++j) {
        int x = i * i + j * j + m * m + 2 * i * j;
        int y = sqrt(x);
        if (y * y == x) {
          cnt += 1;
        }
      }
    }
    printf("m = %d, cnt = %d\n", m, cnt);
    if (cnt >= 1e6) {
      break;
    }
  }
  return 0;
}
