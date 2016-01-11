#include <cstdio>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

#define fst first
#define snd second

map<vector<int>, long long> f, g;

void add(vector<int> v, long long cnt) {
  if (g.count(v) == 0)
    g[v] = cnt;
  else
    g[v] += cnt;
}

int main() {
  f[{0, 0, 0, 0, 0}] = 1;

  const int n = 70;
  for (int rnd = 0; rnd < n; ++rnd) {
    g.clear();
    for (auto &it: f) {
      auto &S = it.fst;

      add({S[2], S[3], S[4], -S[0], -S[1] - 1}, it.snd);
      add({-S[3], -S[4] + 1, S[0], S[1], S[2]}, it.snd);
    }
    f = g;

    long long ans = 0;
    for (auto &it: f) {
      auto &S = it.fst;

      if (S[1] + S[4] == 0 && S[2] + S[3] == 0 && S[1] + S[2] == 0 && S[0] + S[1] == 0) {
        ans += it.snd;
      }
    }
    printf("%d %lu, ans = %lld\n", rnd + 1, f.size(), ans);
  }
  return 0;
}
