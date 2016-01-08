#include <cstdio>
using namespace std;

const int MOD = 1e9 + 7, N = 10;

struct frac {
  long long x, y;

  frac(): x(0), y(1) {}
  frac(int _x, int _y): x(_x), y(_y) {}
} ;

frac operator + (frac a, frac b) {return frac((a.x * b.y + a.y * b.x) % MOD, a.y * b.y % MOD);}
frac operator - (frac a, frac b) {return a + frac(MOD - b.x, b.y);}
frac operator * (frac a, frac b) {return frac(a.x * b.x % MOD, a.y * b.y % MOD);}
frac operator / (frac a, frac b) {return frac(a.x * b.y % MOD, a.y * b.x % MOD);}

frac M(frac x1, frac y1, frac x2, frac y2) { // return [x1, y1]^T M [x2, y2]
  return frac(12, 1) * x1 * x2 + frac(7, 2) * (x1 * y2 + x2 * y1) + frac(MOD - 12, 1) * y1 * y2;
}

frac Px[N], Py[N];

int main() {
  frac Qx(7, 1), Qy(1, 1);
  Px[1] = frac(13, 1), Py[1] = frac(61, 4);
  Px[2] = frac(MOD - 43, 6), Py[2] = frac(MOD - 4, 1);
  Px[3] = frac(MOD - 19, 2), Py[3] = frac(MOD - 229, 24);

  for (int i = 4; i < N; ++i) {
    frac Dx = Px[i - 2] - Qx, Dy = Py[i - 2] - Qy;
    frac mu = M(Dx, Dy, Px[i - 1], Py[i - 1]) / (frac(625, 1) - M(Px[i - 2], Py[i - 2], Qx, Qy));
    Px[i] = Px[i - 1] + mu * Dx;
    Py[i] = Py[i - 1] + mu * Dy;
    printf("(%lld/%lld, %lld/%lld)\n", Px[i].x, Px[i].y, Py[i].x, Py[i].y);
  }
  return 0;
}
