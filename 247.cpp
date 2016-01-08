#include <cstdio>
#include <cmath>
#include <queue>
using namespace std;

struct node {
  int p, q;
  double x, y, t;

  node(int _p, int _q, double _x, double _y): p(_p), q(_q), x(_x), y(_y) {
    t = (sqrt((_x - _y) * (_x - _y) + 4) - (_x + _y)) / 2;
  }
};

bool operator < (node a, node b) {
  return a.t < b.t;
}

priority_queue<node> H;

int main() {
  H.push(node(0, 0, 1, 0));
  for (int n = 1, cnt = 0; ; ++n) {
    node v = H.top(); H.pop();
    // printf("%d %d %.6f %.6f %.6f\n", v.p, v.q, v.x, v.y, v.t);
    H.push(node(v.p, v.q + 1, v.x, v.y + v.t));
    H.push(node(v.p + 1, v.q, v.x + v.t, v.y));
    cnt += v.p == 3 && v.q == 3;
    if (v.p == 3 && v.q == 3)
      printf("%d %d %.6f %.6f %.6f\n", v.p, v.q, v.x, v.y, v.t);
    if (cnt == 20) {
      printf("ans = %d\n", n);
      break;
    }
  }
  return 0;
}
