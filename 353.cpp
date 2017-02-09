#include "fmt/format.h"
#include <cmath>
#include <algorithm>
#include <tuple>
#include <map>
#include <queue>
using namespace fmt;
using namespace std;

const int N = 3e5;
const double pi = acos(-1);
const double cube_sizes[] = {0, 1.5, 1, 1, 0.5, 0.5, 0.2, 0.3, 0.15, 0.15, 0.07, 0.07, 0.05, 0.05, 0.02, 0.02, 0.02, 0.02};

struct node {
    double x, y, z;
};

node p[N];
double dist[N];
int pred[N];
map<tuple<int, int, int>, vector<int>> f;
double cube_size;

bool cmp(node a, node b) {
    if (a.x != b.x) return a.x < b.x;
    if (a.y != b.y) return a.y < b.y;
    return a.z < b.z;
}

double distance(int a, int b) {
    double d = acos(p[a].x * p[b].x + p[a].y * p[b].y + p[a].z * p[b].z);
    return d * d;
}

double l2distance(int a, int b) {
    double dx = p[a].x - p[b].x, dy = p[a].y - p[b].y, dz = p[a].z - p[b].z;
    return max(abs(dx), max(abs(dy), abs(dz)));
}

tuple<int, int, int> locate(int id) {
    return {(1 + p[id].x) / cube_size, (1 + p[id].y) / cube_size, (1 + p[id].z) / cube_size};
}

double dijkstra(int n) {
    int S = 1, T = n;
    for (int i = 1; i <= n; ++i)
        dist[i] = 1e300;

    int max_heap_size = 0;
    priority_queue<pair<double, int>> Q;
    dist[S] = 0, Q.push({0, S});
    while (!Q.empty()) {
        max_heap_size = max(max_heap_size, (int) Q.size());
        auto it = Q.top(); Q.pop();
        int id = it.second; double d = -it.first;
        if (id == T)
            break;
        if (dist[id] < d)
            continue;

        auto loc = locate(id);
        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                for (int dz = -1; dz <= 1; ++dz) {
                    int x = get<0>(loc) + dx, y = get<1>(loc) + dy, z = get<2>(loc) + dz;
                    tuple<int, int, int> pos = {x, y, z};
                    if (!f.count(pos)) continue;
                    for (auto i : f[pos]) {
                        double nd = d + distance(id, i);
                        if (nd < dist[i]) {
                            dist[i] = nd;
                            pred[i] = id;
                            Q.push({-dist[i], i});
                        }
                    }
                }
            }
        }
    }
    if (dist[T] > 1e100) {
        print("xxx\n");
    }

    double max_dist = 0;
    for (int v = T; v != S; v = pred[v]) {
        max_dist = max(max_dist, l2distance(v, pred[v]));
    }
    print("max distance: {:.10f}, max heap size = {}\n", max_dist, max_heap_size);
    cube_size = max_dist * 1.5;

    return dist[T];
}

double solve(long n, double cube_size) {
    long cnt = 0;
    for (long i = 0; i * i <= n * n; ++i)
        for (long j = 0; j * j + i * i <= n * n; ++j) {
            long s = n * n - i * i - j * j;
            long t = sqrt(s);
            if (t * t == s) {
                double x = 1. * i / n, y = 1. * j / n, z = 1. * t / n;
                p[++cnt] = (node){x, y, z};
                if (i) p[++cnt] = (node){-x, y, z};
                if (j) p[++cnt] = (node){x, -y, z};
                if (t) p[++cnt] = (node){x, y, -z};
                if (i && j) p[++cnt] = (node){-x, -y, z};
                if (j && t) p[++cnt] = (node){x, -y, -z};
                if (t && i) p[++cnt] = (node){-x, y, -z};
                if (i && j && t) p[++cnt] = (node){-x, -y, -z};
            }
        }
    print("cnt = {}\n", cnt);
    sort(p + 1, p + cnt + 1, cmp);

    f.clear();
    for (int i = 1; i <= cnt; ++i) {
        auto loc = locate(i);
        f[loc].push_back(i);
    }

    double dist = dijkstra(cnt);

    return dist;
}

int main() {
    double ans = 0;
    cube_size = 1;
    for (int i = 1; i <= 15; ++i) {
        print("----------\n");
        // cube_size = cube_sizes[i];

        print("cube size = {}\n", cube_size);
        double cur = solve((1 << i) - 1, 0.01);
        print("Computing {}: {:.10f}\n", i, cur);
        ans += cur;
    }
    print("{:.10f}\n", ans / pi / pi);
    return 0;
}
