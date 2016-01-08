#include <cstdio>
#include <set>
#include <algorithm>
using namespace std;

#define fst first
#define snd second

const int n = 18, N = n + 10;

set<pair<int, int>> S[N];

int gcd(int a, int b) {
  return a ? gcd(b % a, a) : b;
}

pair<int, int> simplify(int a, int b) {
  int t = gcd(a, b);
  return make_pair(a / t, b / t);
}

int main() {
  S[1].insert(make_pair(1, 1));

  set<pair<int, int>> ans;
  ans.insert(make_pair(1, 1));

  for (int i = 2; i <= n; ++i) {
    for (int j = 1; j <= i - j; ++j) {
      for (auto &p : S[j]) {
        for (auto &q : S[i - j]) {
          int a = p.fst * q.fst;
          int b = p.fst * q.snd + p.snd * q.fst;
          int c = p.snd * q.snd;

          S[i].insert(simplify(a, b));
          S[i].insert(simplify(b, c));
        }
      }
    }

    int max_snd = 0;
    for (auto &p : S[i]) {
      ans.insert(p);
      max_snd = max(max_snd, p.snd);
    }

    printf("size[%d] = %d, ans = %d, max snd = %d\n", i, S[i].size(), ans.size(), max_snd);
  }
  return 0;
}
