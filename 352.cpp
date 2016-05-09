#include <cstdio>
#include <queue>
#include <cmath>
using namespace std;

const int n = 25;
const double p = 0.1;

priority_queue<double, vector<double>, greater<double>> Q;

void dfs(int d, double prob) {
  if (d == 0) {
    Q.push(prob);
    return;
  }
  dfs(d - 1, prob *      p );
  dfs(d - 1, prob * (1 - p));
}

int main() {
  dfs(n, 1);

  double ans = 0;
  while (Q.size() > 1) {
    if (Q.size() % 1000000 == 0)
      printf("%d\n", (int)Q.size());
    double x = Q.top(); Q.pop();
    double y = Q.top(); Q.pop();
    double z = x + y;
    // printf("%.6f %.6f\n", x, y);
    ans += z;
    Q.push(z);
  }
  printf("%.6f\n", ans);
  return 0;
}
