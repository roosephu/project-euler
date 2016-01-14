#include <cstdio>
#include <set>
using namespace std;

#define fst first
#define snd second

typedef pair<double, double> point;

const int n = 5000;

int s[n * 4 + 10];
point p[n * 2 + 10];

double cross(point a, point b, point c) {
  return (b.fst - a.fst) * (c.snd - b.snd) - (b.snd - a.snd) * (c.fst - b.fst);
}

point solve(point p1, point p2, point p3, point p4) {
  if (cross(p1, p2, p3) * cross(p1, p2, p4) < 0 && cross(p3, p4, p1) * cross(p3, p4, p2) < 0) {
    double pa = p1.snd - p2.snd, pb = p2.fst - p1.fst, pc = p1.fst * p2.snd - p2.fst * p1.snd;
    double qa = p3.snd - p4.snd, qb = p4.fst - p3.fst, qc = p3.fst * p4.snd - p4.fst * p3.snd;
    double xa = pb * qc - qb * pc, xb = pc * qa - qc * pa, xc = pa * qb - qa * pb;
    return {xa / xc, xb / xc};
  }
  return {-1, -1};
}

int main() {
  // point x = solve({46, 53}, {17, 62}, {46, 70}, {22, 40});
  // point x = solve({27, 44}, {12, 32}, {46, 70}, {22, 40});
  // printf("%.3f %.3f\n", x.fst, x.snd);
  // return 0;

  s[0] = 290797;
  for (int i = 0; i < n * 4; ++i)
    s[i + 1] = (long long)s[i] * s[i] % 50515093;
  for (int i = 1; i <= n * 2; ++i)
    p[i] = {s[2 * i - 1] % 500, s[2 * i - 0] % 500};
  for (int i = 1; i <= 10; ++i)
    printf("%f %f %f %f\n", p[i * 2 - 1].fst, p[i * 2 - 1].snd, p[i * 2].fst, p[i * 2].snd);

  set<pair<double, double>> S;
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      auto x = solve(p[i * 2 + 1], p[i * 2 + 2], p[j * 2 + 1], p[j * 2 + 2]);
      S.insert(x);
    }
  }
  printf("%d\n", (int)S.size() - 1);
  return 0;
}
