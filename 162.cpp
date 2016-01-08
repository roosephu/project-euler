#include <cstdio>
using namespace std;

const int n = 16;

long long cb[20][20];

long long pow(long long k, int e) {
  return e ? pow(k, e - 1) * k : 1;
}

long long solve(int n, int k) {
  long long ret = 0;
  for (int i = 0; i <= k; ++i)
    ret += cb[k][i] * pow(16 - i, n) * (i % 2 == 0 ? 1 : -1);
  return ret;
}

int main() {
  for (int i = 0; i < 20; ++i)
    for (int j = 0; j <= i; ++j)
      cb[i][j] = j ? cb[i - 1][j - 1] + cb[i - 1][j] : 1;

  long long ans = 0;
  for (int i = 16; i >= 1; --i) {
    ans += solve(i - 1, 3) * 13;
    ans += solve(i - 1, 2) * 2;
  }
  printf("%llX\n", ans);
  return 0;
}
