#include <cstdio>
#include <set>
#include <cmath>
#include <algorithm>
#include <vector>
#include <map>
#include <tuple>
using namespace std;

#define fst first
#define snd second

const int n = 100000;
const long n2 = 1ll * n * n;

map<pair<tuple<long, long, long>, tuple<long, long, long>>, set<long>> h;
map<tuple<long, long, long>, set<long>> f;
map<long, set<tuple<long, long, long>>> g;

int solve(int a, int b, int &x, int &y) {
  if (a == 0) {
    x = 0, y = 1;
    return b;
  }
  int t = solve(b % a, a, y, x);
  x -= b / a * y;
  return t;
}

int main() {
  set<pair<long, long>> T;
  int idx = 0;
  long ans = 0;
  for (long i = 1; i * i <= n * 4; i += 2) {
    for (long j = 1; j <= i; j += 2) {
      // long lb = ((1 - j) * (1 - j) + 1) * (1 + (1 - i) * (1 - i)) * (i * i + j * j);
      // if (lb > n2 * 4) break;
      // solve i * x + j * y = i * j + 1
      int x, y;
      int gcd = solve(i, j, x, y);
      if (gcd != 1) continue;
      if (x <= 0)
        x += j;
      else
        y += i;

      double r = hypot(x - j, y) * hypot(x, y - i) * hypot(i, j) / 2;
      if (r > n) continue;
      long r2 = ((x - j) * (x - j) + y * y) * (x * x + (y - i) * (y - i)) * (i * i + j * j);
      if (r2 > n2 * 4) continue;
      ++idx;
      // printf("%d %d %d %d %d %d\n", i, j, x, y, i * x + j * y, i * j + 1);

      // solve -j * p + i * q = (i^2 - j^2)/2
      int p = 0, q = 0, rem = (i + j) * (i - j) / 2;
      for (int t = 1; t <= i; ++t) {
        if ((rem + j * t) % i == 0) {
          p = t;
          q = (rem + j * t) / i;
          break;
        }
      }

      // set<long> pos, neg;
      tuple<long, long, long> quad = {i * i + j * j, i * p + q * j - i * j, p * p + q * q - 2 * i * q + i * i};
      for (int t = 0; ; ++t) {
        long np = p + t * i;
        long nq = q + t * j;
        long d2 = np * np + (nq - i) * (nq - i);
        if (d2 > n2) break;
        if (d2 * 4 > r2) {
          // if (g[idx].size() < 10 && (idx == 10 || idx == 12))
          //   printf("d2 = %ld, np = %ld, nq = %ld\n", d2, np, nq - i);
          // pos.insert(d2);
          if (f[quad].count(d2))
            break;
          f[quad].insert(d2);
        }
      }
      // long size = f[quad].size();

      // for (int t = -1; ; --t) {
      //   int np = p + t * i;
      //   int nq = q + t * j;
      //   long d2 = 1ll * np * np + 1ll * (nq - i) * (nq - i);
      //   if (d2 > n2) break;
      //   if (d2 * 4 > r2)
      //     neg.insert(d2);
      // }
      // for (auto &u : pos)
      //   for (auto &v : neg)
      //     if (u <= v)
      //       T.insert({u, v});
      printf("(%ld, %ld): %ld, |dist| = %ld, idx = %d\n", i, j, r2, f[quad].size(), idx);
      // for (auto a : pos) {
      //   printf("%lld\n", a);
      // }
      // for (auto b : neg) {
      //   printf("%lld\n", b);
      // }

      // for (auto it : S) {
      //   printf("%lld %lld\n", it.fst, it.snd);
      // }

    }
  }

  int multiple = 0, pairs = 0;
  for (auto &x : f)
    for (auto &y : x.snd)
      g[y].insert(x.fst);
  for (auto &x : g)
    for (auto &y0 : x.snd)
      for (auto &y1 : x.snd)
        if (y0 < y1)
          h[{y0, y1}].insert(x.fst);

  for (auto &x : f) {
    ans += x.snd.size() * (x.snd.size() + 1) / 2;
    // for (auto &a : x.snd)
    //   for (auto &b : x.snd)
    //     if (a <= b)
    //       T.insert({a, b});
  }
  printf("BF = %ld\n", T.size());

  set<pair<long, long>> tried_pairs;
  for (auto &p : h) {
    // if (p.snd.size() > 1)
    //   printf("%ld\n", p.snd.size());
    for (auto &x : p.snd) {
      for (auto &y : p.snd) {
        if (x <= y) {
          if (tried_pairs.count({x, y}) > 0)
            continue;
          tried_pairs.insert({x, y});
          printf("try a pair (%ld, %ld)\n", x, y);
          ++ans;
          for (auto &sets : f)
            if (sets.snd.count(x) > 0 && sets.snd.count(y) > 0)
              --ans;
        }
      }
    }
  }
  printf("|f| = %ld, multiple = %d, |h| = %ld, pairs = %d\n", f.size(), multiple, h.size(), pairs);

  // ans = S.size();
  // ans += g.size();
  printf("ans = %ld\n", ans);
  return 0;
}
