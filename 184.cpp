#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;

const int n = 105, N = n * n * 4 * 2;
const double eps = 1e-8;

double pa[N];
int top;

int gcd(int a, int b) {
  return a ? gcd(b % a, a) : b;
}

int main() {
  double pi = acos(-1);
  for (int i = -n; i <= n; ++i)
    for (int j = -n; j <= n; ++j)
      if (i * i + j * j < n * n && (i || j)) {
        ++top;
        pa[top] = atan2(j, i);
      }

  sort(pa + 1, pa + top + 1);
  for (int i = 1; i <= top; ++i)
    pa[i + top] = pa[i] + pi * 2;
  printf("top = %d\n", top);

  long long ans = 1ll * top * (top - 1) * (top - 2) / 6;
  // for (int i = 1, px = 1; i <= top; ++i) {
  //   while (pa[px] < pa[i] + pi - eps)
  //     ++px;
  //   // printf("%f -> %f\n", pa[i], pa[px]);
  //   ans -= 1ll * (px - i - 1) * (px - i - 2) / 2;
  // }
  for (int i = 1; i <= top / 2; ++i) {
    int cnt = 1;
    for (; pa[i + 1] - pa[i] <= eps; ++i)
      ++cnt;
    // printf("%d\n", cnt);
    // ans -= cnt * cnt * (top - cnt * 2);
    ans -= 1ll * (top / 2 - cnt) * (top / 2 - cnt - 1) * cnt;
    ans -= 1ll * cnt * cnt * (top - cnt * 2) + 1ll * cnt * (cnt - 1) * (top / 2 - cnt);
    ans -= 1ll * (cnt * 2) * (cnt * 2 - 1) * (cnt * 2 - 2) / 6;
  }
  printf("%lld\n", ans);
  return 0;
}
