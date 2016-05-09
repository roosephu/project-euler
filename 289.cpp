#include <cstdio>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

#define fst first
#define snd second

const int n = 2, m = 2, P = n * m * 4 + 10;

typedef vector<pair<int, int>> State;

vector<int> G[P];
int lmt[P];

int get_id(int x, int y, int k) {
  return ((x - 1) * m + (y - 1)) * 4 + k + 1;
}

void adde(int x, int y) {
  if (x > y) return adde(y, x);
  G[y].push_back(x);
  lmt[x] = max(lmt[x], y);
}

void transit(map<State, long> &dp, const State &old, State delta, int cur, long val, bool circle_allowed=false) {
  map<int, int> g;
  for (auto &p : old) {
    g[p.fst] = p.snd;
    g[p.snd] = p.fst;
  }

  for (auto &p : delta) {
    int x = p.fst, y = p.snd; // x -> y
    // printf("%d %d\n", x, y);
    if (x == cur && x != y && g.count(y) == 0)
      return;
    if (y == cur && x != y && g.count(x) == 0)
      return;
    int l = g.count(x) ? g[x] : x, r = g.count(y) ? g[y] : y;
    if (l != x)
      g.erase(x);
    if (r != y)
      g.erase(y);
    if (x != y && l == y && r == x) { // circle
      if (!circle_allowed)
        return;
      continue;
    }
    g[l] = r;
    g[r] = l;
  }

  State s;
  for (auto &it : g) {
    if (it.fst <= it.snd) {
      s.push_back(it);
      if (lmt[it.fst] <= cur || lmt[it.snd] <= cur) // no loop any more
        return;
    }
  }
  if (cur < 20) {
    printf("|  ");
    for (auto it : s)
      printf("(%d -> %d)", it.fst, it.snd);
    printf("\n");
  }

  dp[s] += val;
}

int main() {
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      for (int k = 0; k < 4; ++k) {
        adde(get_id(i, j, k), get_id(i, j, (k + 1) % 4));
      }
      if (i < n) {
        adde(get_id(i, j, 3), get_id(i + 1, j, 1));
        if (j == 1) {
          adde(get_id(i, j, 0), get_id(i + 1, j, 0));
        }
        if (j == m) {
          adde(get_id(i, j, 2), get_id(i + 1, j, 2));
        }
      }

      if (j < m) {
        adde(get_id(i, j, 2), get_id(i, j + 1, 0));
        if (i == 1) {
          adde(get_id(i, j, 1), get_id(i, j + 1, 1));
        }
        if (i == n) {
          adde(get_id(i, j, 3), get_id(i, j + 1, 3));
        }
      }
    }
  }

  const int N = get_id(n, m, 3);
  map<State, long> f;
  f[State()] = 1;

  for (int x = 1; x <= N; ++x) { // adding vertices one by one
    map<State, long> g;
    bool b = x == N;
    printf("cur = %d\n", x);

    for (auto &it : f) {
      if (x < 17) {
        for (auto p : it.fst) {
          printf("(%d -> %d)", p.fst, p.snd);
        }
        printf(" = %ld\n", it.snd);
      }


      transit(g, it.fst, {{x, x}}, x, it.snd, b);

      for (auto y : G[x]) {
        transit(g, it.fst, {{x, y}}, x, it.snd, b);
      }
      for (auto y1 : G[x]) {
        for (auto y2 : G[x]) {
          if (y1 < y2) {
            transit(g, it.fst, {{y1, y2}}, x, it.snd, b);
          }
        }
      }
    }

    f = g;
  }

  long ans = f[State()];
  printf("ans = %ld\n", ans);
  return 0;
}
