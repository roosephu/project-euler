#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cassert>
using namespace std;

#define fst first
#define snd second

const long long MOD = 1e16;

int top = 0, cnt = 0;
pair<double, long long> P[100], ans;
pair<double, long long> Q[(1 << 21) | 10];
double sum = 0;

bool is_prime(int n) {
  for (int i = 2; i * i <= n; ++i)
    if (n % i == 0)
      return false;
  return n != 1;
}

void dfs(bool mode, int L, int R, double l, long long p) {
  if (L > R) {
    assert(p > 0);
    if (mode)
      Q[++cnt] = make_pair(l, p);
    else {
      pair<double, long long> *x = upper_bound(Q + 1, Q + cnt + 1, make_pair(sum - l, 0ll)) - 1;
      pair<double, long long> cur = make_pair(x->fst + l, x->snd * p % MOD);
      assert(cur.fst <= sum);
      if (cur > ans) {
        ans = cur;
        printf("%lld * %lld\n", x->snd, p);
      }
    }
    return ;
  }
  pair<double, long long> x = P[L];
  dfs(mode, L + 1, R, l        , p              );
  dfs(mode, L + 1, R, l + x.fst, p * x.snd % MOD);
}

int main() {
  for (int i = 2; i <= 190; ++i) {
    if (is_prime(i)) {
      ++top;
      P[top] = make_pair(log(i), i);
      sum += log(i);
    }
  }
  sum /= 2;

  dfs(true, top / 2 + 1, top, 0, 1);
  printf("sum = %.6f, top = %d\n", sum, top);
  sort(Q + 1, Q + cnt + 1);
  printf("sorted.\n");

  dfs(false, 1, top / 2, 0, 1);

  printf("log(ans) = %.6f\n", ans.fst);
  return 0;
}
