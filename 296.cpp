#include <cstdio>
#include <algorithm>
using namespace std;

const int n = 100000;

int gcd(int a, int b) {
  return a ? gcd(b % a, a) : b;
}

int main() {
  long long ans = 0;
  for (int x = 1; x <= n; ++x) {
    if (x % 100 == 1)
      printf("%d\n", x);
    for (int y = x; y <= n; ++y) {
      int sxy = y + x;
      if (sxy + y > n)
        break;
      int dvs = sxy / gcd(x, y);
      int zmin = y, zmax = min(sxy - 1, n - sxy);
      ans += zmax / dvs - (zmin - 1) / dvs;
      // for (int z = zmin; z <= zmax; ++z)
      //   if (z % dvs == 0)
      //     ++ans;
          // printf("%d %d %d\n", x, y, z);
    }
  }
  printf("%lld\n", ans);
  return 0;
}
