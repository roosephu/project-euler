#include <cstdio>
using namespace std;

const long long L = 1e13, R = 1e14, init = 7e6;
// const long long L = 1e4, R = 1e5, init = 2e2;

long long ans = 0;
int cnt = 0;

long long step(long long n, long long x) {
  return (x + (n + x - 1) / x) / 2;
}

void dfs(long long L, long long R, long long init) {
  ++cnt;
  if (cnt % 3000000 == 0)
    printf("current interval: [%lld, %lld] with init = %lld\n", L, R, init);
  ans += R - L;
  long long Ln = step(L, init), Rn = step(R - 1, init);

  for (long long i = Ln + 1; i <= Rn + 1; ++i) {
    long long start = (2 * i - init - 1) * init + 1;
    // if (i != step(start, init) || i == step(start - 1, init)) {
    //   printf("FATAL: start = %lld, next = %lld, init = %lld; got next = %lld\n", start, i, init, step(start - 1, init));
    //   while (1);
    // }
    if (start > R)
      start = R;
    if (init != i - 1)
      dfs(L, start, i - 1);
    L = start;
  }
}

int main() {
  dfs(L, R, init);
  printf("answer = %lld, rate = %.10f\n", ans, 1. * ans / (R - L));

  // ans = 0;
  // for (int i = L; i < R; ++i) {
  //   int x = init;
  //   for (; ; ) {
  //     int y = step(i, x);
  //     ans++;
  //     if (x == y)
  //       break;
  //     x = y;
  //   }
  // }
  // printf("answer = %lld, rate = %.6f\n", ans, 1. * ans / (R - L));
  return 0;
}
