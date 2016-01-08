#include <cstdio>
#include <algorithm>
using namespace std;

const int n = 7;

int sub[10][140];
int val[10];
int lmt;
int found = false;

bool merge(int l, int *a, int *b, int *r) {
  int x = 0, y = 0;
  for (int i = 0; x < l || y < l; ++i)
    if (y == l || (x < l && a[x] < b[y]))
      r[i] = a[x], ++x;
    else if (x == l || (y < l && b[y] < a[x]))
      r[i] = b[y], ++y;
    else
      return false;
  return true;
}

void dfs(int d, int v, int s) {
  if (d == n) {
    int xs = val[0], ys = 0;
    for (int i = 1, j = d - 1; i < j; ++i, --j) {
      xs += val[i], ys += val[j];
      if (xs < ys) return ;
    }
    for (int i = 0; i < d; ++i)
      printf("%d", val[i]);
    printf(" = %d\n", s);
    found = true;
    lmt = s;
    return ;
  }
  int tmp[129] = {0};
  for (int i = 0; i < (1 << d); ++i)
    tmp[i] = sub[d][i] + v + 1;
  for (int x = v + 1; ; ++x) {
    if (s > lmt)
      return;
    if (merge(1 << d, tmp, sub[d], sub[d + 1]))
      val[d] = x, dfs(d + 1, x, s);
    for (int i = 0; i < (1 << d); ++i)
      ++tmp[i];
    s += n - d;
  }
}

int main() {
  lmt = 100;
  int init = 15;
  for (; !found; lmt += 20) {
    printf("current limit = %d\n", lmt);
    dfs(0, init, init * n + n * (n + 1) / 2);
  }

  return 0;
}
