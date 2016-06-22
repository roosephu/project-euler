#include <cstdio>
#include <algorithm>
#include <map>
#include <cmath>
#include <tuple>
using namespace std;

// https://en.wikipedia.org/wiki/Apollonian_gasket
double solve(double a, double b, double c) {
    a = 1 / a, b = 1 / b, c = 1 / c; // from radius to curvature
    return 1 / (a + b + c + 2 * sqrt(a * b + b * c + c * a));
}

map<tuple<int, double, double, double>, double> f;

double dfs(int dep, double a, double b, double c) {
    if (dep == 10)
        return 0;
    if (a > b) swap(a, b);
    if (b > c) swap(b, c);
    if (a > b) swap(a, b);
    auto h = tuple<int, double, double, double>(dep, a, b, c);
    if (f.count(h) == 0) {
        double x = solve(a, b, c);
        double ret = x * x;
        ret += dfs(dep + 1, x, b, c);
        ret += dfs(dep + 1, a, x, c);
        ret += dfs(dep + 1, a, b, x);
        f[h] = ret;
    }
    return f[h];
}

int main() {
    double t = sqrt(3);
    double O = -2 - t;
    double L = t;
    double R = t;
    double U = t;
    printf("%f\n", solve(L, R, U));
    printf("%f\n", solve(L, R, O));

    double area = 3 * t * t;
    area += dfs(0, L, R, O) * 3;
    area += dfs(0, L, R, U);
    area /= (2 + t) * (2 + t);
    printf("ans = %.10f\n", 1 - area);
    return 0;
}
