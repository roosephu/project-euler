#include <vector>
#include "fmt/format.h"
#include <cmath>
#include <queue>
#include <cstdlib>
using namespace std;
using namespace fmt;

// https://link.springer.com/article/10.1007%2FBF01840404
const int n = 500, N = n + 10;

struct node {
    double x, y, angle;
};

node points[N];
int S[N * 2];
deque<int> Q[N];
vector<int> in[N], out[N];
double L[N][N];

bool cmp(node a, node b) {
    return a.angle < b.angle;
}

bool cmp_x(node a, node b) {
    return a.x > b.x;
}

double cross(int a, int b, int c) {
    return (points[b].x - points[a].x) * (points[c].y - points[a].y) - (points[c].x - points[a].x) * (points[b].y - points[a].y);
}

void proceed(int i, int j) {
    while (!Q[i].empty() && cross(Q[i].front(), i, j) > 0) {
        proceed(Q[i].front(), j);
        Q[i].pop_front();
    }
    // print("adding edge: {} -> {}\n", i, j);
    out[i].push_back(j);

    Q[j].push_back(i);
}

int main() {
    int n = ::n;
    S[0] = 290797;
    for (int i = 1; i <= n * 2; ++i)
        S[i] = (long)S[i - 1] * S[i - 1] % 50515093;

    for (int i = 1; i <= n; ++i) {
        double x = S[2 * i - 1] % 2000 - 1000;
        double y = S[2 * i - 0] % 2000 - 1000;

        x += rand() % 10 * 1e-5;
        y += rand() % 10 * 1e-5;
        points[i] = (node){x, y};
    }
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            for (int k = 1; k <= n; ++k)
                if (i != j && j != k && i != k && cross(i, j, k) == 0)
                    print("colinear.\n");
                    // print("{}({}, {}) {}({}, {}) {}({}, {})\n", i, x[i], y[i], j, x[j], y[j], k, x[k], y[k]);
    // return 0;
    // points[2] = points[n], --n;
    // points[4] = points[n], --n;
    // points[5] = points[n], --n;
    // points[6] = points[n], --n;
    // points[7] = points[n], --n;
    // for (int i = 1; i <= n; ++i) {
    //     print("({}, {})\n", points[i].x, points[i].y);
    // }

    double ans = 0;
    for (int p = n; p; --p) {
        sort(points + 1, points + p + 1, cmp_x);
        for (int i = 1; i < p; ++i)
            points[i].angle = atan2(points[i].y - points[p].y, points[i].x - points[p].x);
        sort(points + 1, points + p, cmp);

        // print("current point: ({:.0f}, {:.0f})\n", points[p].x, points[p].y);

        for (int i = 1; i <= p - 1; ++i) {
            Q[i].clear();
            in[i].clear();
            out[i].clear();
        }
        for (int i = 1; i <= p - 2; ++i)
            proceed(i, i + 1);
        for (int i = 1; i <= p - 1; ++i)
            for (auto j : out[i]) {
                in[j].push_back(i);
                L[i][j] = 0;
            }

        for (int i = p - 1; i; --i) {
            double m = 0;
            for (int j = in[i].size() - 1, l = out[i].size() - 1; j >= 0; --j) {
                while (l >= 0 && cross(i, in[i][j], out[i][l]) < 0) {
                    m = max(m, L[i][out[i][l]]);
                    --l;
                }
                double weight = cross(p, in[i][j], i);
                L[in[i][j]][i] = m + weight;
            }
        }

        for (int i = 1; i <= p - 1; ++i) {
            for (auto j : out[i]) {
                // print("p = {}, {}({}, {}) -> {}({}, {}), L = {}\n", p, i, points[i].x, points[i].y, j, points[j].x, points[j].y, L[i][j]);
                if (L[i][j] > ans) {
                    ans = L[i][j];
                }
            }
        }
    }
    print("ans = {:.3f}\n", ans / 2);

    return 0;
}
