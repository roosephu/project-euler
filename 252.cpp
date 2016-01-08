#include <cstdio>
#include <vector>
#include <cmath>
using namespace std;

const int n = 500, N = n + 10;

vector<int> T[N][N];
int x[N], y[N];
int S[N * 2];
int idx[N];
double ang[N];

bool cmp(int a, int b) {
  return ang[a] < ang[b];
}

int next_to(int i, int j) {
  ++j;
  if (j > n)
    return i + 1;
  return j;
}

double cross(int i, int j, int k) {
  return (x[i] - x[j]) * (y[k] - y[j]) - (x[k] - x[j]) * (y[i] - y[j]);
}

int main() {
  S[0] = 290797;
  for (int i = 1; i <= n * 2; ++i)
    S[i] = (long long)S[i - 1] * S[i - 1] % 50515093;

  for (int i = 1; i <= n; ++i) {
    x[i] = S[2 * i - 1] % 2000 - 1000;
    y[i] = S[2 * i - 0] % 2000 - 1000;
  }
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j)
      for (int k = 1; k <= n; ++k)
        if (i != j && j != k && i != k && cross(i, j, k) == 0)
          printf("%d(%d, %d) %d(%d, %d) %d(%d, %d)\n", i, x[i], y[i], j, x[j], y[j], k, x[k], y[k]);
  return 0;

  for (int i = 1; i <= n; ++i) {
    for (int j = i + 1; j <= n; ++j) {
      idx[j] = j;
      ang[j] = atan2(y[j] - y[i], x[j] - x[i]);
    }
    sort(idx + i + 1, idx + n + 1);

    for (int j = i + 1; j <= n; ++j) { // deciding triangles i --- j
      int last = 0;
      for (int k = next_to(i, j); k != j; k = next_to(i, k)) {
        if (cross(idx[j], i, idx[k]) <= 0) // wrong direction
          break;
        if (last == 0 || cross(last, idx[j], idx[k]) > 0) {
          last = idx[k];
          T[i][idx[j]].push_back(idx[k]);
        }
      }
    }
  }
  return 0;
}
