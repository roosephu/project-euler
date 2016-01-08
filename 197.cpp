#include <cstdio>
#include <cmath>
using namespace std;

double f(double x) {
  return floor(pow(2, 30.403243784 - x * x)) / 1e9;
}

int main() {
  double u = -1;
  for (int i = 1; i <= 1000; ++i) {
    u = f(u);
    printf("%.9f\n", u + f(u));
  }
  return 0;
}
