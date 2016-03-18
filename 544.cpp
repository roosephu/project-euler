#include <cstdio>
#include <map>
#include <algorithm>
using namespace std;

const int MOD = 1e9 + 7;
const int M = 20;

int color[M];

int decode(long state, int m) {
  int ret = 0;
  for (int i = 1; i <= m; ++i) {
    color[i] = state >> (i * 4) & 15;
    ret = max(ret, color[i]);
  }
  return ret;
}

long encode(int m) {
  int map[M] = {0}, cnt = 0;
  for (int i = 1; i <= m; ++i) {
    if (color[i] != 0 && map[color[i]] == 0) {
      ++cnt;
      map[color[i]] = cnt;
    }
  }

  long ret = 0;
  for (int i = 1; i <= m; ++i)
    ret += (long)map[color[i]] << (4 * i);
  return ret;
}

long compute(int n, int m, int k) {
  map<long, long> f;
  f[0] = 1;
  for (int x = 1; x <= n; ++x) {
    for (int y = 1; y <= m; ++y) {
      map<long, long> g;
      for (auto &it : f) {
        int max_color = decode(it.first, m), old = color[y];
        for (int i = 1; i <= max_color + 1; ++i) {
          if (i != old && i != color[y - 1]) {
            color[y] = i;
            long state = encode(m);
            int sols = i > max_color ? k - max_color : 1;
            (g[state] += sols * it.second) %= MOD;
          }
        }
      }
      f = g;
    }
  }

  long ret = 0;
  for (auto &it : f) {
    ret += it.second;
  }
  return ret % MOD;
}

int main() {
  // long ans = 0;
  // for (int i = 1; i <= 15; ++i)
  //   ans += compute(4, 4, i);
  // printf("ans = %ld\n", ans % MOD);
  for (int c = 0; c <= 100; ++c) {
    printf("%ld\n", compute(10, 9, c));
  }
  return 0;
}
