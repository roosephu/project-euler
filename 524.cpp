#include <cstdio>
#include <algorithm>
#include <cassert>
using namespace std;

typedef long long int64;

const int64 L = 8916100448256ll;

int perm[100];
bool used[100];
int cnt_bin[65536];

int64 count_perm(int *perm, int n) {
  int64 ret = 0;
  int mx = 0;
  for (int i = 1; i <= n; ++i) {
    // assert(1 <= perm[i] && perm[i] <= n);
    if (perm[i] > mx) {
      mx = perm[i];
    } else {
      int cnt = 0;
      for (int j = 1; j < i; ++j)
        if (perm[j] < perm[i])
          ++cnt;
      ret += 1ll << cnt;
    }
  }
  return ret;
}

bool is_possible(int *prefix, int n, int finished, int64 rank) {
  int64 lb = 0, ub = 0;
  int cur_max = 0;
  for (int i = 1; i <= finished; ++i) {
    cur_max = max(cur_max, prefix[i]);
  }

  // lower bound
  for (int pos = finished + 1, x = max(cur_max - 1, 0), y = cur_max + 1; pos <= n; ++pos) {
    while (x > 0 && used[x])
      --x;
    if (x == 0) {
      while (used[y])
        ++y;
      prefix[pos] = y;
      y += 1;
    } else {
      prefix[pos] = x;
      x -= 1;
    }
  }
  lb = count_perm(prefix, n);

  // upper bound
  int ub_pos = finished + 1;
  if (!used[n]) {
    prefix[ub_pos] = n;
    ub_pos += 1;
  }
  for (int pos = ub_pos, x = 1, y = n; pos <= n; ++pos) {
    while (used[x])
      ++x;
    prefix[pos] = x;
    x += 1;
  }
  ub = count_perm(prefix, n);
  // printf("%lld %lld %lld\n", lb, ub, rank);

  return lb <= rank && rank <= ub;
}

int popcnt(int64 x) {
  int ret = 0;
  while (x) {
    ret += cnt_bin[x & 65535];
    x >>= 16;
  }
  return ret;
}

void dfs(int n, int dep) {
  // printf("dep: %d ", dep);
  int64 current = count_perm(perm, dep - 1);
  if (popcnt(L - current) > (n - dep + 1)) {
    if (dep < 35)
      printf("cut bin @ %d: %d %d\n", dep, popcnt(L - current), n - dep + 1);
    return;
  }
  if (!is_possible(perm, n, dep - 1, L)) {
    if (dep < 35)
      printf("cut @ %d\n", dep);
    return;
  }
  if (dep > n) {
    for (int i = 1; i <= n; ++i) {
      printf("%d\n", perm[i]);
    }
    return;
  }
  for (int i = 1; i <= n; ++i) {
    if (used[i])
      continue;
    used[i] = true;
    perm[dep] = i;
    dfs(n, dep + 1);
    used[i] = false;
  }
}

int main() {
  // for (int i = 1; i < 65536; ++i)
  //   cnt_bin[i] = cnt_bin[i >> 1] + (i & 1);
  // int n = 1;
  // while (!is_possible(perm, n, 0, L) && n <= 50)
  //   ++n;
  // printf("%d\n", n);
  // dfs(n, 1);

  int n = 45;
  perm[1] = 1;
  for (int i = 2, pos = 1; i <= n; ++i) {
    if (L >> (i - 2) & 1) {
      perm[pos] = i;
      perm[i] = i - 1;
    } else {
      perm[i] = i;
      pos = i;
    }
  }
  for (int i = 1; i <= n; ++i) {
    printf("%d ", perm[i]);
  }
  printf("\n");

  // perm[1] = 4, perm[2] = 3, perm[3] = 2, perm[4] = 1, n = 4;
  int64 fac = 1, ans = 1;
  for (int i = n; i; --i) {
    for (int j = i + 1; j <= n; ++j)
      if (perm[i] > perm[j])
        ans += fac;
    fac *= n - i + 1;
  }
  printf("%lld %lld %lld\n", count_perm(perm, n), L, ans);
  return 0;
}
