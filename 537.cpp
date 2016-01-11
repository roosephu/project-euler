#include <cstdio>
using namespace std;

const int MOD = 1004535809, g = 3;
const int M = 65536;

long long aux[M], ws[M], iw[M], x[M], y[M];

long long fpm(long long b, long long e, long long m) {
  long long t = 1;
  for (; e; e >>= 1, b = b * b % m)
    e & 1 ? t = t * b % m : 0;
  return t;
}

bool is_prime(int x) {
  for (int i = 2; i * i <= x; ++i)
    if (x % i == 0)
      return false;
  return x != 1;
}

void FFT(long long *x, int n, int o, long long *w) {
  if (n == 1) return;
  int m = n / 2;
  FFT(x           , n / 2, o + 1, w);
  FFT(x + (1 << o), n / 2, o + 1, w);

  int t = 0;
  for (int i = 0; i < m; ++i) {
    long long u = x[(i * 2) << o], v = x[(i * 2 + 1) << o];
    aux[t++] = (u + v * w[M / n * i]) % MOD;
    aux[t++] = (u - v * w[M / n * i] % MOD + MOD) % MOD;
  }
  for (int i = 0, t = 0; i < m; ++i) {
    x[     i  << o] = aux[t++];
    x[(m + i) << o] = aux[t++];
  }
}

void mul(long long *x, long long *y, int n) {
  long long inv = fpm(M, MOD - 2, MOD);
  for (int j = 0; j < M; ++j)
    y[j] = x[j] * y[j] % MOD * inv % MOD;
  FFT(y, M, 0, iw);
  for (int j = n + 1; j < M; ++j)
    y[j] = 0;
}

int main() {
  int n = 20000, k = 20000;
  for (int i = 2, pi = 0; pi <= n; ++i) {
    ++x[pi];
    pi += is_prime(i);
  }

  for (int i = 0; i < M; ++i)
    ws[i] = fpm(g, (MOD - 1) / M * i, MOD);
  for (int i = 0; i < M; ++i)
    iw[i] = ws[(M - i) % M];

  y[0] = 1;
  for (; k; k >>= 1) {
    printf("%d\n", k);
    if (k & 1) {
      FFT(x, M, 0, ws);
      FFT(y, M, 0, ws);
      mul(x, y, n);
      mul(x, x, n);
    } else {
      FFT(x, M, 0, ws);
      mul(x, x, n);
    }
  }
  printf("ans = %lld\n", y[n]);

  return 0;
}
