#include <cstdio>
#include <cmath>
using namespace std;

const int n = 1e4;

int main() {
  int ans = 0;
  for (int i = 5; i <= n; ++i) {
    double best = -1e300;
    int idx = 0;
    for (int j = 1; j <= i; ++j) {
      double cur = j * log((double)i / j);
      if (cur > best) {
        best = cur;
        idx = j;
      }
    }
    while (idx % 2 == 0)
      idx /= 2;
    while (idx % 5 == 0)
      idx /= 5;

    if (i % idx == 0)
      ans -= i;
    else
      ans += i;
  }
  printf("%d\n", ans);
  return 0;
}
