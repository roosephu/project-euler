#include <cstdio>
#include <cmath>
using namespace std;

int main() {
  int ans = 0;
  for (int i = 2; i <= 15; ++i) {
    double p = 1;
    for (int x = 1; x <= i; ++x) {
      double v = x * 2. / (i + 1);
      p *= pow(v, x);
    }
    ans += p;
    printf("%d %.3lf\n", i, p);
  }
  printf("%d\n", ans);
  return 0;
}
