#include <cstdio>
using namespace std;

const int edges[10][2] = {{6, 7}, {1, 2}, {1, 3}, {1, 6}, {2, 3}, {2, 7}, {3, 4}, {4, 5}, {5, 6}, {5, 7}};
const int A = 25, B = 75, C = 1984;
const int MOD = 1e8;

long long f, g;
int color[10];
int cb[A + B + 10][A + B + 10];

bool check(int start) {
  for (int i = start; i < 10; ++i) {
    int u = edges[i][0];
    int v = edges[i][1];
    if (color[u] == color[v])
      return false;
  }
  return true;
}

void dfs(int d, int c) {
  if (d == 0) {
    for (int i = 1; i <= c; ++i) {
      bool b = false;
      for (int j = 1; j <= 7; ++j)
        if (color[j] == i)
          b = true;
      if (!b)
        return ;
    }
    long long t = 1;
    for (int i = 2; i < c; ++i)
      t = t * (C - i) / (i - 1);
    if (check(0))
      (f += t) %= MOD;
    if (check(1))
      (g += t) %= MOD;
    return;
  }
  if (d == 1 || d == 6)
    return dfs(d - 1, c);
  for (int i = 1; i <= c; ++i) {
    color[d] = i;
    dfs(d - 1, c);
  }
}

int main() {
  color[1] = 1, color[6] = 2;
  for (int i = 1; i <= 7; ++i)
    dfs(7, i);
  printf("f = %lld, g = %lld\n", f, g);

  for (int i = 0; i <= A + B; ++i)
    for (int j = 0; j <= i; ++j)
      cb[i][j] = j ? (cb[i - 1][j - 1] + cb[i - 1][j]) % MOD : 1;
  long long ans = cb[A + B][B];
  for (int i = 1; i <= A; ++i)
    ans = ans * f % MOD;
  for (int i = 1; i <= B; ++i)
    ans = ans * g % MOD;

  ans = ans * C % MOD * (C - 1) % MOD;
  printf("%lld\n", ans);
  return 0;
}
