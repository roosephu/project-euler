#include <cstdio>
#include <algorithm>
using namespace std;

int n = 7;

int sub[15][10000];
int val[15];
int lmt;
int found = false;
int ans = 0;

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

void dfs(int d) {
  if (d == n) {
    int xs = val[0], ys = 0;
    for (int i = 1, j = d - 1; i < j; ++i, --j) {
      xs += val[i], ys += val[j];
      if (xs < ys) return ;
    }
    int s = 0;
    for (int i = 0; i < d; ++i)
      printf("%d", val[i]), s += val[i];
    printf(" = %d\n", s);
    ans += s;
    return ;
  }
  int tmp[12900] = {0};
  for (int i = 0; i < (1 << d); ++i)
    tmp[i] = sub[d][i] + val[d];
  if (merge(1 << d, tmp, sub[d], sub[d + 1]))
    dfs(d + 1);
}

int main() {
  freopen("p105_sets.txt", "r", stdin);
  char s[1000];
  for (; ; ) {
    s[0] = 0;
    gets(s);
    if (!s[0])
      break;
    n = 0;
    int v = 0;
    for (int i = 0; ; ++i) {
      if (s[i] == ',')
        val[n++] = v, v = 0;
      else if (!s[i]) {
        val[n++] = v;
        break;
      } else
        v = v * 10 + s[i] - '0';
    }
    sort(val, val + n);
    printf("%d\n", n);
    dfs(0);
  }
  printf("ans = %d\n", ans);
  return 0;
}
