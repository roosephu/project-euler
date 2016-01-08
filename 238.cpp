#include <cstdio>
using namespace std;

int main() {
  long long s0 = 14025256;
  int cnt = 0;

  for (long long x = s0, y = s0; ; ) {
    // printf("%lld", x);
    x = x * x % 20300713;
    y = y * y % 20300713;
    y = y * y % 20300713;
    ++cnt;
    if (x == y) {
      break;
    }
  }
  printf("%d\n", cnt);
  return 0;
}
