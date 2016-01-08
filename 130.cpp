#include <cstdio>
using namespace std;

bool is_prime(int x) {
  for (int i = 2; i * i <= x; ++i)
    if (x % i == 0)
      return false;
  return x != 1;
}

long long fpm(long long b, long long e, long long m) {
  long long t = 1;
  for (; e; e >>= 1, b = b * b % m)
    e & 1 ? t = t * b % m : 0;
  return t;
}

int main() {
  int ans = 0;
  for (int i = 2, cnt = 25; cnt; ++i) {
    if (i % 2 == 0 || i % 5 == 0 || is_prime(i))
      continue;
    if (fpm(10, i - 1, 9 * i) == 1) {
      --cnt;
      ans += i;
      printf("find: %d\n", i);
    }
  }
  printf("%d\n", ans);
  return 0;
}
