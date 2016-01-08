#include <cstdio>
#include <map>
using namespace std;

const int n = 80, m = 64 * 27 * 25 * 7 * 11 * 13;

int top;
long long Q[n], ans;
int o[n];
map<long long, int> F;

void dfs(int b, int L, int R, long long sum) {
  if (L > R) {
    if (b) {
      if (F.count(sum) == 0)
        F[sum] = 1;
      else
        ++F[sum];
    } else {
      sum = 1ll * m * m / 2 - sum;
      if (F.count(sum)) {
        printf("new: ");
        for (int i = top / 2 + 1; i <= top; ++i)
          if (o[i] == 1 && 1ll * m * m / Q[i] % 13 == 0) {
            printf("%lld ", 1ll * m * m / Q[i]);
          }
        printf("\n");
        ans += F[sum];
      }
    }
    return ;
  }

  o[L] = 0, dfs(b, L + 1, R, sum       );
  o[L] = 1, dfs(b, L + 1, R, sum + Q[L]);
}

int main() {
  for (int i = 2; i <= n; ++i) {
    if (m % i == 0) {
      ++top;
      Q[top] = 1ll * (m / i) * (m / i);
    }
  }

  printf("m = %d, top = %d\n", m, top);
  dfs(1, 1, top / 2, 0);
  printf("F.size = %d\n", (int)F.size());
  dfs(0, top / 2 + 1, top, 0);
  printf("ans = %lld\n", ans);
  return 0;
}
