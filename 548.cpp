#include <cstdio>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

const long long n = 1e16, inf = (long long)1e16 + 2;
const int m = 14;

int primes[m] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43};
map<vector<int>, long long> f;
int expo[m], dvs[m], cnt;

long long dfs2(int dep) {
  long long ret = 0;
  if (dep < 0) {
    vector<int> v(dvs, dvs + 14);
    sort(v.rbegin(), v.rend());
    return f[v];
  }
  for (int i = 0; i <= expo[dep]; ++i) {
    dvs[dep] = i;
    ret += dfs2(dep - 1);
  }
  return min(ret, inf);
}

void dfs(long long cur, int dep, int last_exp, bool dup) {
  if (cur != 1) {
    vector<int> v(expo, expo + m);
    f[v] = 0;
    fill(dvs, dvs + m, 0);
    long long val = !dup ? dfs2(dep) : inf;
    f[v] = val;
    if (val > n)
      dup = true;
    // if (val > n) return;

    ++cnt;
    printf("cnt = %d, ", cnt);
    for (int i = 0; i < m; ++i)
      printf("%d ", expo[i]);
    printf(": %lld\n", val);
  }
  for (int i = 1; i <= last_exp; ++i) {
    cur *= primes[dep];
    expo[dep] = i;
    if (cur > n) break;
    dfs(cur, dep + 1, i, dup);
  }
  expo[dep] = 0;
}

int main() {
  f[vector<int>(expo, expo + m)] = 1;
  dfs(1, 0, 64, false);

  // for (auto &it : f) {
  //   for (auto &k : it.first) {
  //     printf("%d ", k);
  //   }
  //   printf(": %lld\n", it.second);
  // }
  printf("%d\n", (int)f.size());
  return 0;
}
