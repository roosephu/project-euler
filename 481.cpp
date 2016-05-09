#include <cstdio>
#include <vector>
using namespace std;

const int n = 14, N = n + 2;

double s[N];
double p[1 << n | 100][N][N];
double f[1 << n | 100][N];
int del[1 << n | 100][N];

void solve(int S, double *p) {
    double cur_p = 1, sum = 0;
    for (int d = 0; d < n; ++d) {
        int u = d;
        if (S >> u & 1) {
            sum += cur_p * p[u];
            cur_p *= 1 - s[u];
        }
    }
    p[0] = sum / (1 - cur_p);

    for (int d = n - 1; d; --d) {
        int u = d;
        if (S >> u & 1) {
            p[u] += (1 - s[u]) * p[(u + 1) % n];
            // if (d == n) {
            //     printf("new = %.6f, old = %.6f\n", p[S][u][v], sum);
            // }
        } else {
            p[u] = p[(u + 1) % n];
        }
    }
}

int main() {
    s[0] = 0.25;
    s[1] = 0.5;
    s[2] = 1;
    int a = 0, b = 1;
    for (int i = 0; i < n; ++i) {
      int c = a + b;
      a = b, b = c;
      s[i] = a;
    }
    for (int i = 0; i < n; ++i)
      s[i] /= b;

    for (int i = 0; i < n; ++i)
        for (int x = 0; x < n; ++x)
            p[1 << i][i][x] = 1;

    for (int S = 0; S < (1 << n); ++S) {

        vector<int> xs;
        for (int i = 0; i < n; ++i)
            if (S >> i & 1) {
                xs.push_back(i);
            }
        if (xs.size() >= 2) {
            for (auto v : xs) {
                double max_p = -1;
                for (auto u : xs) {
                    double cur_p = p[S ^ (1 << u)][v][(v + 1) % n];
                    if (cur_p > max_p) {
                        max_p = cur_p;
                        del[S][v] = u;
                    }
                }
            }

            for (auto v : xs) {
                for (int u = 0; u < n; ++u)
                    if (S >> u & 1)
                        p[S][v][u] = s[u] * p[S ^ (1 << del[S][u])][v][(u + 1) % n];

                solve(S, p[S][v]);
            }
            for (int u = 0; u < n; ++u)
                if (S >> u & 1)
                    f[S][u] = 1 + s[u] * f[S ^ (1 << del[S][u])][(u + 1) % n];
            solve(S, f[S]);
        }
    }
    // for (int S = 0; S < (1 << n); ++S)
    //     for (int u = 0; u < n; ++u) {
    //         printf("p[%d][%d] = [", S, u);
    //         for (int v = 0; v < n; ++v)
    //             printf("%.6f, ", p[S][v][u]);
    //         printf("]\n");
    //     }
    for (int i = 0; i < n; ++i) {
        printf("w[%d] = %.8f\n", i, p[(1 << n) - 1][i][0]);
    }
    printf("ans = %.8f\n", f[(1 << n) - 1][0]);
    return 0;
}
