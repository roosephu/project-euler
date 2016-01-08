#include <cstdio>
using namespace std;

const long long n = 13082761331670030ll;

int main() {
  long long x = n;
  for (long long i = 2; i * i <= x; ++i) {
    if (x % i == 0) {
      int cnt = 0;
      for (; x % i == 0; x /= i)
        ++cnt;
      printf("find: %lld^%d\n", i, cnt);
    }
  }
  if (x != 1) {
    printf("find: %lld^%d\n", x, 1);
  }
  return 0;
}
