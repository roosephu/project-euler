#include <cstdio>
#include <vector>
using namespace std;

const int n = 13;

int primes[6] = {2, 3, 5, 7, 11, 13};
int cnt[6] = {10, 5, 2, 1, 1, 1};
int power[6];
int idx[20];
vector<long long> candidates[2000];
int top;
vector<long long> ans;

bool is_prime(long long n) {
  for (long long i = 2; i * i <= n; ++i)
    if (n % i == 0)
      return false;
  return n != 1;
}

void dfs(int d, long long x) {
  if (d == 6) {
    if (is_prime(x + 1)) {
      vector<long long> v;
      v.push_back(x + 1);
      for (int i = 0; i < 6; ++i)
        v.push_back(power[i]);

      ++top;
      candidates[top] = v;
    }
    return ;
  }
  for (int i = 0; i <= cnt[d]; ++i) {
    power[d] = i;
    dfs(d + 1, x);
    x *= primes[d];
  }
}

void dfs2(int d, vector<long long> v) {
  if (d == 0) {
    for (int i = 0; i < 6; ++i)
      if (v[i + 1] != 0)
        return ;
    // printf("%lld\n", v[0]);
    ans.push_back(v[0]);
    return ;
  }

  dfs2(d - 1, v);
  v[0] *= candidates[d][0];
  // printf("%lld\n", candidates[d][0]);
  for (int i = 0; i < 6; ++i) {
    v[i + 1] -= candidates[d][i + 1];
    if (v[i + 1] < 0)
      return ;
  }
  dfs2(d - 1, v);
  if (candidates[d][0] > 13)
    return ;

  int p = idx[candidates[d][0]];
  for (; ; ) {
    v[0] *= candidates[d][0];
    // printf("%lld\n", candidates[d][0]);
    v[p + 1]--;
    if (v[p + 1] < 0)
      return ;
    dfs2(d - 1, v);
  }
}

int main() {
  dfs(0, 1);
  sort(candidates + 1, candidates + top + 1);
  for (int i = 1; i <= top; ++i) {
    printf("%lld", candidates[i][0]);
    for (int j = 0; j < 6; ++j)
      printf(" %lld", candidates[i][j + 1]);
    printf("\n");
  }
  for (int i = 0; i < 6; ++i)
    idx[primes[i]] = i;

  vector<long long> v;
  v.push_back(1);
  for (int i = 0; i < 6; ++i)
    v.push_back(cnt[i]);
  dfs2(top, v);

  sort(ans.begin(), ans.end());
  printf("number = %d, first = %lld\n", (int)ans.size(), ans[0]);
  printf("first = %lld, ans = %lld\n", ans[0], ans[150000 - 1]);
  return 0;
}
