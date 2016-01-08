#include <cstdio>
#include <cmath>
using namespace std;

double f(double x) {
  double dx = x - 0.25, dy = sqrt(0.0625 - dx * dx);
  double y = 0, z = 1;
  for (int i = 0; i <= 30; ++i) {
    if (x < 0.5)
      y += z * x;
    else
      y += z * (1 - x);

    x *= 2;
    z /= 2;
    if (x >= 1)
      x -= 1;
  }
  double l = fmax(0.5 - dy, 0), r = fmin(0.5 + dy, y);
  // printf("%.6f %.6f %.6f\n", x, dy, y);
  return l < r ? r - l : 0;
}

double area(double L, double R, double fl, double fm, double fr) {
  return (R - L) * (fl + fm * 4 + fr) / 6;
}

double simpson(double L, double m, double R, double fl, double fm, double fr, double s) {
  double Lm = (L + m) / 2, flm = f(Lm);
  double mR = (m + R) / 2, fmr = f(mR);
  double sl = area(L, m, fl, flm, fm), sr = area(m, R, fm, fmr, fr);
  if (abs(s - sl - sr) <= 1e-15)
    return sl + sr + (sl + sr - s) / 15;
  return simpson(L, Lm, m, fl, flm, fm, sl) + simpson(m, mR, R, fm, fmr, fr, sr);
}

int main() {
  double L = 0, m = 0.25, R = 0.5, fl = f(L), fm = f(m), fr = f(R), s = area(L, R, fl, fm, fr);
  printf("fl = %.6f, fm = %.6f, fr = %.6f, extra = %.6f\n", fl, fm, fr, f(0.1));
  printf("%.8f\n", simpson(L, m, R, fl, fm, fr, s));
  return 0;
}
