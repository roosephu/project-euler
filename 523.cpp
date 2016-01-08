#include <cstdio>
using namespace std;

int main() {
  double f = 0, ans = 0;
  const int n = 30;
  for (int i = 1; i <= n; ++i) {
    ans += f / i;
    f = f * 2 + 1;
  }
  printf("%.2f\n", ans);
  return 0;
}
