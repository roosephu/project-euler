#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

const int N = 7e5;

struct node {
  double x, y, z;
};

node p[N];
double dist[N];

bool cmp(node a, node b) {
  if (a.x != b.x) return a.x < b.x;
  if (a.y != b.y) return a.y < b.y;
  return a.z < b.z;
}

double distance(int a, int b) {
  double d = acos(p[a].x * p[b].x + p[a].y * p[b].y + p[a].z * p[b].z);
  return d * d;
}

double solve(long long n, int LMT) {
  long long cnt = 0;
  for (long long i = 0; i * i <= n * n; ++i)
    for (long long j = 0; j * j + i * i <= n * n; ++j) {
      long long s = n * n - i * i - j * j;
      long long t = sqrt(s);
      if (t * t == s) {
        double x = 1. * i / n, y = 1. * j / n, z = 1. * t / n;
        p[++cnt] = (node){x, y, z};
        if (i != 0) p[++cnt] = (node){-x, y, z};
        if (j != 0) p[++cnt] = (node){x, -y, z};
        if (t != 0) p[++cnt] = (node){x, y, -z};
        if (i && j) p[++cnt] = (node){-x, -y, z};
        if (j && t) p[++cnt] = (node){x, -y, -z};
        if (t && i) p[++cnt] = (node){-x, y, -z};
        if (i && j && t) p[++cnt] = (node){-x, -y, -z};
      }
    }
  sort(p + 1, p + cnt + 1, cmp);
  for (int i = 1; i <= cnt; ++i)
    dist[i] = 1e300;
  dist[1] = 0;

  for (int i = 1; i <= cnt; ++i) {
    for (int j = 1; j <= LMT && i + j <= cnt; ++j) {
      dist[i + j] = min(dist[i + j], dist[i] + distance(i, i + j));
    }
  }

  double pi = acos(-1);
  return dist[cnt] / pi / pi;
}

int main() {
  double ans = 0;
  for (int i = 1; i <= 15; ++i) {
    double cur = solve((1 << i) - 1, 40000);
    printf("Computing %d: %.10f\n", i, cur);
    ans += cur;
  }
  printf("%.10f\n", ans);
  return 0;
}
