#include <cstdio>
#include <map>
#include <cmath>
using namespace std;

const int m = 18000000, M = m + 10;

long f[3][M];
map<pair<long, long>, long> g;

long get(long x, int lv) {
  if (x <= m)
    return f[lv][x];

  auto s = make_pair(x, lv);
  if (g.count(s) != 0)
    return g[s];

  long ret;
  if (lv == 0) {
    long L = 1, R = 1, m;
    while (get(R, 1) < x) {
      L = R + 1;
      R *= 2;
    }
    for (; m = (L + R) >> 1, L < R; )
      get(m, 1) >= x ? R = m : L = m + 1;
    ret = m;
  } else if (lv == 1) {
    long y = get(x, 0), rem = x - get(y - 1, 1);
    ret = get(y - 1, 2) + rem * y;
  } else {
    printf("FAIL: %ld\n", x);
    return 0;
  }
  g[s] = ret;
  return ret;
}

int main() {
  f[0][1] = 1, f[0][2] = 2;
  for (int i = 3, cnt = 1, now = 2; i <= m; ++i) {
    f[0][i] = now;
    if (cnt == 1) {
      ++now;
      cnt = f[0][now];
    } else {
      --cnt;
    }
  }
  for (int i = 1; i <= m; ++i) {
    f[1][i] = f[1][i - 1] + f[0][i];
    f[2][i] = f[2][i - 1] + f[0][i] * i;
  }
  printf("f(1e6, 0) = %ld\n", get(1e6, 0));

  long ans = 0;
  for (long i = 1; i < 1e6; ++i) {
    long v = get(i * i * i, 0);
    if (i % 1000 == 0)
      printf("%ld: G(%ld) = %ld\n", i, i * i * i, v);
    ans += v;
  }

  printf("f0[m] = %ld, f1[m] = %ld, f2[m] = %ld\n", f[0][m], f[1][m], f[2][m]);
  printf("ans = %ld\n", ans);
  return 0;
}
