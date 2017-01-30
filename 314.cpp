#include "fmt/format.h"
#include <algorithm>
using namespace fmt;
using namespace std;

const int n = 250, N = n + 10;

struct node {
    double area, peri;
};

double ratio;
node f[N][N];

bool operator < (node a, node b) {
    return (a.area - a.peri * ratio) < (b.area - b.peri * ratio);
}

node find() {
    for (int i = 0; i <= n; ++i)
        f[0][i] = (node){0., (double) i};
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= n; ++j) {
            f[i][j] = (node){-1e300, 0};
            for (int x = 0; x < i; ++x) {
                for (int y = 0; y <= j; ++y) {
                    f[i][j] = max(f[i][j], (node){f[x][y].area + (j + y) * (i - x) / 2., f[x][y].peri + hypot(x - i, j - y)});
                }
            }
        }
    }
    return f[n][n];
}

int main() {
    for (double last = 140; ; ) {
        ratio = last;
        node ans = find();
        last = ans.area / ans.peri;
        print("{:.8f}\n", last);
        if (fabs(last - ratio) < 1e-10)
            break;
    }
    return 0;
}