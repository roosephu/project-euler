#include <cstdio>
#include <map>
#include <tuple>
using namespace std;

const long long MOD = 1e9, n = 1234567890123ll;
const int m = 24;

long long cnt[m + 1];
map<long long, long long> fibonacci;

int gcd(int a, int b) {
  return a ? gcd(b % a, a) : b;
}

int check(int a, int b, int c) {
  int ans = a + b + c + 1;
  for (int n = 1; n <= ans; ++n) {
    ans = gcd(ans, n * (c + n * (b + n * (a + n))));
  }
  return ans;
}

long long mul(long long a, long long b, long long MOD) {
  long long t = 0;
  for (; b; b >>= 1, a = (a + a) % MOD)
    b & 1 ? t = (t + a) % MOD : 0;
  return t;
}

long long fib(long long n, long long MOD) {
  if (!fibonacci.count(n)) {
    long long a = fib(n / 2, MOD), b = fib(n / 2 + 1, MOD), ret = 0;
    if (n % 2 == 0) {
      ret = mul(a, 2 * b + MOD - a, MOD);
    } else {
      ret = (mul(a, a, MOD) + mul(b, b, MOD)) % MOD;
    }
    fibonacci[n] = ret;
  }
  return fibonacci[n];
}

typedef tuple<int, int, int, int> node;

node step(node a, int x) {
  return node(get<1>(a), (get<0>(a) + get<1>(a)) % m, get<2>(a) + 1, get<3>(a) + (get<1>(a) + m - x) % m);
}

long long count(int x) {
  long long cur_MOD = m * MOD;
  // long long a = 0, b = 1;
  // long long ans = 0;
  // for (int i = 1; i <= n; ++i) {
  //   long long c = (a + b) % cur_MOD;
  //   a = b;
  //   b = c;
  //   ans += (a + m - x) / m;
  // }
  // return ans;

  long long ret = fib(n + 2, cur_MOD) - 1 + (m - x) * n % cur_MOD, steps = n;
  node A(0, 1, 0, 0), B(0, 1, 0, 0);
  for (; steps; ) {
    A = step(A, x);
    B = step(B, x);
    B = step(B, x);
    --steps;
    if (get<0>(A) == get<0>(B) && get<1>(A) == get<1>(B)) {
      long long periods = steps / (get<2>(B) - get<2>(A)) % cur_MOD;
      steps -= periods * (get<2>(B) - get<2>(A)) % cur_MOD;
      ret   -= periods * (get<3>(B) - get<3>(A)) % cur_MOD;
    }
  }
  ret -= get<3>(A);
  ret = (cur_MOD + ret % cur_MOD) % cur_MOD;
  // printf("%lld %lld: ret = %lld, ", ret, ret % m, ret / m);
  ret /= m;

  // long long ans = 0;
  // for (int a = 0, b = 1, i = 0; i < n; ++i) {
  //   int c = a + b;
  //   a = b;
  //   b = c;
  //   ans += (a + m - x) / m;
  // }
  // printf("ans = %lld\n", ans);

  return ret;

  // return (n - x + m) / m;
}

long long compute(long long n) {
  long long ans = 0;
  for (int a = 1; a <= m; ++a)
    for (int b = 1; b <= m; ++b)
      for (int c = 1; c <= m; ++c)
        ans += ((n + m - a) / m) * ((n + m - b) / m) * ((n + m - c) / m) * check(a, b, c);
  return ans;
}

long long g[100];

int main() {
  fibonacci[1] = 1;
  fibonacci[2] = 1;
  // for (int i = 1; i <= 10; ++i)
  //   printf("%lld\n", fib(i, 1000000));
  // return 0;

  for (int i = 1; i <= 60; ++i)
    g[i] = compute(i);
  for (int x = 0; x <= 4; ++x) {
    for (int i = 60; i; --i)
      g[i] -= g[i - 1], printf("%lld ", g[i]);
    printf("\n");
  }
  // for (int b = 2; b <= 2; ++b)
  //   for (int a = 0; a <= 4; ++a)
  //     printf("{%d, %lld},", a, compute(a * m + b));

  // for (int i = 1; i <= m; ++i)
  //   cnt[i] = count(i) % MOD;
  // --cnt[1];

  return 0;
}
