#include <cstdio>
using namespace std;

const int n = 100, N = n + 10;

int f[N];

void solve(long long p, long long q) {
  if (q == 0)
    return;
  if (p > q) { // add 0
    long long pp = (p - 1) % q + 1;
    solve(pp, q);
    printf("%lld,", (p - pp) / q);
  } else { // add 1
    long long qq = q % p;
    solve(p, qq);
    printf("%lld,", (q - qq) / p);
  }
}

int main() {
  f[0] = 1;
  for (int i = 1; i <= n; ++i) {
    if (i & 1)
      f[i] = f[i / 2];
    else
      f[i] = f[i / 2] + f[i / 2 - 1];

    printf("%d: %d\n", i, f[i]);
  }
  solve(1, 1); printf("\n");
  solve(13, 17); printf("\n");
  solve(3, 2); printf("\n");
  solve(2, 3); printf("\n");
  solve(19, 7); printf("\n");
  solve(7, 19); printf("\n");
  solve(123456789ll / 9, 987654321ll / 9); printf("\n");
  return 0;
}
