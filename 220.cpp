#include <cstdio>
using namespace std;

struct node {
  long long x, y, d, s;
  node(long long _x, long long _y, long long _d, long long _s): x(_x), y(_y), d(_d), s(_s) {}
  node(): x(0), y(0), d(0), s(0) {}
} ;

const node F = node(1, 0, 0, 1), L = node(0, 0, 3, 0), R = node(0, 0, 1, 0);
const int n = 50, N = n + 10;

node A[N], B[N];

node operator + (node a, node b) {
  for (int i = 0; i < a.d; ++i) {
    long long x = b.x, y = b.y;
    b.x = y;
    b.y = -x;
  }
  a.x += b.x;
  a.y += b.y;
  (a.d += b.d) %= 4;
  a.s += b.s;
  return a;
}

void dfs(int n, int type, long long &steps, node &p) {
  if (steps == 0) return ;
  if (type == 0) { // start
    --steps, p = p + F; if (!steps) return ;
    dfs(n, 'a', steps, p);
  } else if (type == 'a') { // one `a` node
    if (steps >= A[n].s) {
      steps -= A[n].s;
      p = p + A[n];
      return ;
    }
    dfs(n + 1, 'a', steps, p); if (!steps) return ;
    p = p + R;
    dfs(n + 1, 'b', steps, p); if (!steps) return ;
    --steps, p = p + F; if (!steps) return ;
    p = p + R;
  } else if (type == 'b') { // one `b` node
    if (steps >= B[n].s) {
      steps -= B[n].s;
      p = p + B[n];
      return ;
    }
    p = p + L;
    --steps, p = p + F; if (!steps) return ;
    dfs(n + 1, 'a', steps, p); if (!steps) return ;
    p = p + L;
    dfs(n + 1, 'b', steps, p); if (!steps) return ;
  }
}

int main() {
  A[n] = B[n] = node(0, 0, 0, 0);
  for (int i = n - 1; i >= 0; --i) {
    A[i] = A[i + 1] + R + B[i + 1] + F + R;
    B[i] = L + F + A[i + 1] + L + B[i + 1];
  }

  long long steps = 1e12;
  node p = node(0, 0, 3, 0);
  dfs(0, 0, steps, p);
  printf("%lld,%lld\n", p.x, p.y);
  return 0;
}
