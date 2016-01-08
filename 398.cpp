#include <cstdio>
#include <cmath>
using namespace std;

const int n = 1e7, N = n + 10, m = 100;

double fac[N];

int o[2222];
int total_count;
long long answer;

double log_cb(int n, int m) {
  if (n < 0 || n < m) return -1e300;
  return fac[n] - fac[m] - fac[n - m];
}

void dfs(int d, int x) {
  if (d == m) {
    o[d] = n;

    int fst = 1e9, snd = 1e9;
    for (int i = 1; i <= m; ++i) {
      int v = o[i] - o[i - 1];
      if (v < fst)
        snd = fst, fst = v;
      else if (v < snd)
        snd = v;
    }

    answer += snd;
    // if (snd != 1) {
    //   for (int i = 1; i <= m; ++i)
    //     printf("label for %d: %d\n", i, o[i]);
    // }
    total_count += 1;
    return ;
  }
  for (int i = x + 1; i <= n - (m - d); ++i) {
    o[d] = i;
    dfs(d + 1, i);
  }
}

int main() {
  for (int i = 1; i <= n; ++i)
    fac[i] = fac[i - 1] + log(i);

  double total = log_cb(n - 1, m - 1);
  printf("total = %.f\n", total);
  double ans = 0;
  for (int i = 0; i <= n / m; ++i) {
    double cur = 1;
    for (int j = 0; j < m - 1; ++j)
      cur = cur * (n - m * i - 1 - j) / (n - 1 - j);
    ans += cur;
    // ans += exp(log_cb(n - m * i - 1, m - 1) - total);
    // if (i > 0)
    //   for (int j = 0; j <= n / (m - 1); ++j)
    //     ans += m * exp(log_cb(n - m * i - 1 - (m - 1) * j, m - 2) - total);
  }

  for (int x = 0; x <= n - 1 - m; ++x) {
    // try to count how many solutions of m*i + (m-1)*j = x, where i >= 0, j >= 0
    int lo_i = x % (m - 1), hi_i = x / m;
    if (lo_i <= hi_i) {
      int cnt = (hi_i - lo_i) / (m - 1) + 1;

      double cur = (m - 1) / (n - 1 - (m - 2.));
      for (int j = 0; j < m - 2; ++j)
        cur = cur * (n - 1 - m - x - j) / (n - 1 - j);

      ans += 1. * m * cnt * cur; // exp(log_cb(n - 1 - m - x, m - 2) - total);
    }
  }

  // printf("answer = %d, count = %d, ratio = %.6f\n", answer, total_count, 1.);
  // dfs(1, 0);
  // printf("answer = %lld, count = %d, ratio = %.6f\n", answer, total_count, 1. * answer / total_count);

  printf("%.7f\n", ans);
  return 0;
}
