#include <cstdio>
#include <map>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

#define fst first
#define snd second

const int n = 11, M = 60;
const double eps = 1e-9;

int o[20];
bool visited[20];
double G[M][M], dist[M], weight[M], fac[M];
map<vector<int>, int> f;

void dfs(int n, vector<int> s, double prob) {
  if (n == 0) {
    sort(s.begin(), s.end());
    if (f.count(s) == 0) {
      int id = f.size();
      f[s] = id;
      printf("%d:", id);
      for (auto x : s)
        printf(" %d", x);
      printf("\n");
    }
    weight[f[s]] += prob;
    return;
  }
  for (int i = 1; i <= n; ++i) {
    vector<int> v = s;
    v.push_back(i);
    dfs(n - i, v, prob / n);
  }
}

int main() {
  // dfs(n, 0, n);
  // fac[0] = 1;
  // for (int i = 1; i <= n; ++i)
  //   fac[i] = fac[i - 1] * i;
  dfs(n, vector<int>(), 1);

  double sum = 0;
  for (int i = 0; i < f.size(); ++i)
    printf("%.5f\n", weight[i]), sum += weight[i];
  printf("sum: %.5f\n", sum);

  for (auto it : f) {
    if (it.snd == 0)
      continue;
    int cnt = 0;
    vector<int> perm;
    for (auto v : it.fst) {
      int old = cnt;
      for (int i = 2; i <= v; ++i) {
        ++cnt;
        perm.push_back(cnt);
      }
      perm.push_back(old);
      ++cnt;
    }

    double prob = 1. / n / (n - 1) / (n - 2);
    for (int a = 0; a < n; ++a)
      for (int b = a + 1; b < n; ++b)
        for (int c = b + 1; c < n; ++c) {
          int old[] = {a, b, c}, pos[] = {a, b, c};
          do {
            auto next = perm;
            for (int i = 0; i < 3; ++i)
              next[pos[i]] = perm[old[i]];
            vector<int> circles;
            for (int i = 0; i < n; ++i)
              visited[i] = false;

            for (int i = 0; i < n; ++i) {
              if (visited[i])
                continue;
              int size = 0;
              for (; !visited[i]; i = next[i])
                visited[i] = true, ++size;

              if (size > 0)
                circles.push_back(size);
            }

            sort(circles.begin(), circles.end());
            auto id = f[circles];
            G[it.snd][id] += 1;
          } while (next_permutation(pos, pos + 3));
        }
  }

  int m = f.size();
  for (int i = 1; i < m; ++i)
    for (int j = 0; j < m; ++j)
      G[i][j] /= n * (n - 1) * (n - 2);
  for (int i = 1; i <= m; ++i)
    G[i][m] = 1;
  for (int t = 0; t < 100; ++t) {
    double F[M][M] = {0};
    for (int i = 0; i <= m; ++i)
      for (int j = 0; j <= m; ++j)
        for (int k = 0; k <= m; ++k)
          F[i][k] += G[i][j] * G[j][k];
    for (int i = 0; i <= m; ++i)
      for (int j = 0; j <= m; ++j)
        G[i][j] = F[i][j];
  }
  dist[m] = 1;

  double ans = 0;
  for (int _ = 0; ; ++_) {
    double tmp[M] = {0};
    for (int i = 1; i < m; ++i) {
      double d = 0;
      for (int j = 0; j <= m; ++j)
        d += G[i][j] * dist[j];
      tmp[i] = d;
    }
    double diff = 0;
    for (int i = 0; i < m; ++i) {
      diff += abs(dist[i] - tmp[i]);
      dist[i] = tmp[i];
    }

    double new_ans = 0;
    for (int i = 1; i < m; ++i)
      new_ans += dist[i] * weight[i];
    if (diff < eps && diff > -eps)
      break;
    ans = new_ans;
    printf("%.5f\n", ans);
  }
  printf("ans = %.5f\n", ans);

  return 0;
}
