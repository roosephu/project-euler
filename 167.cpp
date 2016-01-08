#include <cstdio>
using namespace std;

const long long k = 1e11;

void step(int n, int &X, int &xs) {
  int first = X & 1, last = X >> (2 * n + 1) & 1;
  int cur = first != last;
  X = ((X << 1) ^ (last << (2 * n + 2))) | cur;
  xs += cur;
}

long long solve(int n, long long k) {
  int X = 1, Y = 1, xs = 1, ys = 1;
  long long ans = 2 * n + 1;

  k -= 2;
  for (int i = 1; ; ++i) {
    if (xs == k)
      return ans;
    ans += 2;
    step(n, X, xs);
    // if (X & 1)
    //   printf("%d: %lld\n", xs, ans);
    step(n, Y, ys);
    step(n, Y, ys);
    if (X == Y) {
      long long diff = ys - xs;
      long long period = (k - xs) / diff;
      ans += period * i * 2;
      k -= diff * period;
      printf("diff = %lld, period = %lld\n", diff, period);
    }
  }
  return -1;
}

int main() {
  // printf("%lld\n", solve(2, 61));
  // return 0;

  long long ans = 0;
  for (int n = 2; n <= 10; ++n)
    ans += solve(n, k);
  printf("%lld\n", ans);
  return 0;
}
