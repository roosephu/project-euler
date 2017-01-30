#include "fmt/format.h"
#include <NTL/ZZ.h>
#include <vector>
#include <algorithm>
#include <map>
#include <tuple>
using namespace fmt;
using namespace NTL;
using namespace std;

const int n = 120;

struct node {
    int x, y, z;
    double a;
};

vector<node> v;
int cnt;
int coef[10000];
map<tuple<int, int, int, int, int>, long> f;

int abs(int x) {
    return x > 0 ? x : -x;
}

bool cmp(node a, node b) {
    return a.a < b.a;
}

long dfs(int dep, int c, int x, int y, int z) {
    if (z + hypot(x, y) > n + 0.001)
        return 0;
    tuple<int, int, int, int, int> s = {dep, min(c, 3), x, y, z};
    if (f.count(s) == 0) {
        ++cnt;
        long ret = 0;
        if (x == 0 && y == 0 && c > 2) {
            // print("dep = {}\n", c);
            // for (int i = 0; i < v.size(); ++i)
            //     if (coef[i] > 0) {
            //         print("{} {} {}\n", v[i].x, v[i].y, coef[i]);
            //     }
            ret = 1;
        }

        for (int i = dep; i < v.size(); ++i) {
            for (int t = 1; t * v[i].z + z <= n; ++t) {
                // coef[i] = t;
                ret += dfs(i + 1, c + 1, x + v[i].x * t, y + v[i].y * t, z + v[i].z * t);
                // coef[i] = 0;
            }
        }
        f[s] = ret;
    }
    return f[s];
}

int main() {
    for (int x = -n; x <= n; ++x) {
        for (int y = -n; y <= n; ++y) {
            if (GCD(abs(x), abs(y)) == 1) {
                int z = hypot(x, y);
                if (z * z == x * x + y * y && z * 2 <= n) {
                    v.push_back((node){x, y, z, hypot(y, x)});
                }
            }
        }
    }
    // sort(v.begin(), v.end(), cmp);
    // for (auto it : v) {
    //     print("{} {} {}\n", it.x, it.y, it.z);
    // }

    long ans = dfs(0, 0, 0, 0, 0);
    print("ans = {}, cnt = {}\n", ans, cnt);
    return 0;
}