#include <cstdio>
#include <algorithm>
using namespace std;

const long long LMT = 1e12;

bool is_prime(long long x) {
  for (long long i = 2; i * i <= x; ++i)
    if (x % i == 0)
      return false;
  return x != 1;
}

long long Q[1000], ans = 0;
int top = 0;

void dfs(int d, long long v, long long l) {
  if (d == top || Q[d] > l) {
    for (long long x = v; x <= LMT; x *= 2)
      for (long long y = x; y <= LMT; y *= 3)
        for (long long z = y; z <= LMT; z *= 5)
          ans += (unsigned int)z;
    return;
  }
  dfs(d + 1, v       , l       );
  dfs(d + 1, v * Q[d], l / Q[d]);
}

int main() {
  for (long long x = 1; x <= LMT; x *= 2)
    for (long long y = x; y <= LMT; y *= 3)
      for (long long z = y; z <= LMT; z *= 5)
        if (is_prime(z + 1))
          Q[top++] = z + 1;
  sort(Q, Q + top);
  printf("%d %lld %lld\n", top, Q[0], Q[1]);

  dfs(3, 1, LMT);
  printf("ans = %lld\n", ans % (1ll << 32));
  return 0;
}
