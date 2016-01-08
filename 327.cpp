#include <cstdio>
using namespace std;

long long solve(int C, int R) {
  if (C > R)
    return R + 1;
  long long x = solve(C, R - 1);
  long long rep = (x - (C - 1) + (C - 3)) / (C - 2);
  return C * rep + 1 + (x - (C - 2) * rep);
}

int main() {
  long long ans = 0;
  for (int i = 3; i <= 40; ++i)
    ans += solve(i, 30);
  printf("%lld\n", ans);
  return 0;
}
