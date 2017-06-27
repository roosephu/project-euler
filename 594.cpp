#include "fmt/format.h"
#include <cstdlib>
using namespace fmt;
using namespace std;

namespace PE594 {
    const int n = 8, m = 2, N = 10, M = 10;
    const int dx[2] = {1, 0}, dy[2] = {0, -1};

    long ans = 0;
    long f[N][N][N][N];
    int xs[M][M], ys[M][M], X[M][M], Y[M][M];

    long dfs(int cnt_a, int cnt_b, int x1, int y1, int x2, int y2) {
        if (x1 == n && y1 == 0 && x2 == n && y2 == 0)
            return 1;

        if (f[x1][y1][x2][y2] < 0) {
            long ret = 0;

            while (cnt_a <= m && xs[1][cnt_a] == x1 && ys[1][cnt_a] == y1)
                ++cnt_a;
            while (cnt_b <= m && xs[2][cnt_b] == x2 && ys[2][cnt_b] == y2)
                ++cnt_b;
            for (int d1 = 0; d1 <= 1; ++d1) {
                for (int d2 = 0; d2 <= 1; ++d2) {
                    int nx1 = x1 + dx[d1], ny1 = y1 + dy[d1];
                    int nx2 = x2 + dx[d2], ny2 = y2 + dy[d2];
                    if (nx1 > nx2) continue;

                    if (nx1 <= xs[1][cnt_a] && ny1 >= ys[1][cnt_a] && nx2 <= xs[2][cnt_b] && ny2 >= ys[2][cnt_b]) {
                        ret += dfs(cnt_a, cnt_b, nx1, ny1, nx2, ny2);
                    }
                }
            }

            f[x1][y1][x2][y2] = ret;
        }
        return f[x1][y1][x2][y2];
    }

    long dp() {
        memset(f, -1, sizeof(f));
        // print("---\n");
        // for (int i = 1; i <= m; ++i) {
        //     for (int j = 1; j <= m; ++j) {
        //         print("({}, {}) ", X[i][j], Y[i][j]);
        //     }
        //     print("\n");
        // }
        long ret = dfs(1, 1, 0, n, 0, n);
        // print("ret = {}\n", ret);
        return ret;
    }

    void update() {
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= m; ++j) {
                xs[i][j] = X[i][j];
                ys[i][j] = Y[i][j];
            }
        }
        long cnt_X = dp();

        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= m; ++j) {
                xs[m + 1 - j][i] = Y[i][j];
                ys[m + 1 - j][i] = n - X[i][j];
            }
        }
        long cnt_Y = dp();

        ans += cnt_X * cnt_Y;
    }

    void dfs1(int i, int j) {
        if (i > m) return update();
        if (j > m) return dfs1(i + 1, 1);
        for (int x = max(X[i - 1][j], X[i][j - 1]); x <= n; ++x) {
            for (int y = Y[i - 1][j]; y <= Y[i][j - 1]; ++y) {
                X[i][j] = x;
                Y[i][j] = y;
                dfs1(i, j + 1);
            }
        }
    }

    void main() {
        ans = 0;
        for (int i = 1; i <= m; ++i) {
            xs[i][m + 1] = n;
            Y[i][0] = n;
        }
        dfs1(1, 1);
        print("ans = {}\n", ans);
    }
}

int main() {
    PE594::main();
    return 0;
}