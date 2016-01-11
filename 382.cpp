#include <cstdio>
using namespace std;

const int MOD = 1e9, m = 11;
const long long n = 1e18;

typedef long long mat[m][m];

mat U, V;

// ans(n) = ans(n-1) + f(n)
// f_n = g_n + 2^(n-3) + 2^(n-4) + f_(n-3) - 1
// g_n = 2^(n-5) + f_(n-4) + g(n-3) - 1

// [0-3]: f
// [4-7]: g
// 8: 2^(n-5)
// 9: 1
// 10: S

// init: [0, 0, 0, 2, 0, 0, 0, 0, 1, 1, 0]

void matmul(mat a, mat b, mat c) {
  mat t = {0};
  for (int i = 0; i < m; ++i)
    for (int j = 0; j < m; ++j)
      for (int k = 0; k < m; ++k)
        t[i][j] += a[i][k] * b[k][j] % MOD;
  for (int i = 0; i < m; ++i)
    for (int j = 0; j < m; ++j)
      c[i][j] = t[i][j] % MOD;
}

int main() {
  U[0][1] = U[1][2] = U[2][3] = U[4][5] = U[5][6] = U[6][7] = 1;
  U[7][0] = 1, U[7][5] = 1, U[7][8] = 1, U[7][9] = MOD - 1;
  U[3][0] = 1, U[3][5] = 1, U[3][8] = 7, U[3][9] = MOD - 2, U[3][1] = 1;
  U[8][8] = 2;
  U[9][9] = 1;
  U[10][10] = 1, U[10][0] = 1;

  V[3][0] = 2, V[8][0] = 1, V[9][0] = 1;

  for (long long e = n; e; e >>= 1, matmul(U, U, U))
    e & 1 ? matmul(U, V, V), 0 : 0;

  printf("%lld\n", V[10][0]);

  return 0;
}
