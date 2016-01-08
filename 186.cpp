#include <cstdio>
#include <cassert>
using namespace std;

const int N = 1e6, M = 1e8, pm = 524287;

int sz[N], ufs[N], S[M];

int find(int t) {
  return ufs[t] != -1 ? ufs[t] = find(ufs[t]) : t;
}

int main() {
  for (int k = 1; k <= 55; ++k)
    S[k] = (N + 100003ll - 200003LL * k % N + 300007LL * k % N * k % N * k % N) % N;
  for (int k = 56; k < M; ++k)
    S[k] = (S[k - 24] + S[k - 55]) % N;

  int succ = 0;
  for (int i = 0; i < N; ++i)
    sz[i] = 1, ufs[i] = -1;

  int cnt = 0;
  while (sz[find(pm)] < 0.99 * N) {
    int x = 0, y = 0;
    while (x == y) {
      ++cnt;
      assert(cnt * 2 < M);
      x = S[cnt * 2 - 1];
      y = S[cnt * 2    ];
    }

    ++succ;
    int u = find(x), v = find(y);
    if (u != v) {
      ufs[v] = u;
      sz[u] += sz[v];
    }
  }
  printf("%d\n", succ);
  return 0;
}
