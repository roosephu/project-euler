#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

#define fst first
#define snd second

const double pi = acos(-1);

double M(pair<double, double> p, pair<double, double> q) {
  return p.fst * q.fst * 4 + p.snd * q.snd;
}

pair<double, double> intersect(pair<double ,double> p, double theta) {
  pair<double, double> dir = make_pair(cos(theta), sin(theta));
  double mu = -2 * M(dir, p) / M(dir, dir);
  return make_pair(p.fst + mu * dir.fst, p.snd + mu * dir.snd);
}

int main() {
  auto p1 = make_pair(1.4, -9.6);
  double dir = atan2(10.1 + 9.6, 0.0 - 1.4);
  auto p_init = intersect(p1, dir);
  dir = dir - pi;

  for (int n = 0; ; ++n) {
    auto p = intersect(p_init, dir);
    double ref = atan2(-4 * p.fst, p.snd) + pi / 2;

    dir = 2 * ref - dir - pi;
    p_init = p;
    printf("%d: (%.6f, %.6f)\n", n, p.fst, p.snd);

    if (-0.01 <= p.fst && p.fst <= 0.01 && p.snd > 0) {
      printf("ans = %d\n", n);
      break;
    }
  }
  return 0;
}
