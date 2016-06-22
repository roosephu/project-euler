#include <cstdio>
#include <vector>
#include <cmath>
using namespace std;

const long R = 1e7;
double maxLength = 0, ans = 0;

long exgcd(long x, long y, long &p, long &q) {
    if (x == 0) {
        p = 0, q = 1 / y;
        return y;
    }
    long ret = exgcd(y % x, x, q, p), t = y / x;
    p -= t * q;
    return ret;
}

void update(long x1, long y1, long x2, long y2) {
    long dx = x1 - x2, dy = y1 - y2, p = 0, q = 0;
    if (dx * dx + dy * dy < (2 * R - 1) * (2 * R - 1) - 2) return;
    if (dx < 0) dx = -dx;
    if (dy < 0) dy = -dy;
    long g = exgcd(dx, dy, p, q);
    if (g != 1) return;
    double a = hypot(dx, dy);
    if (a + R + 1 / (a + R) <= maxLength / 2) return;
    // printf("%ld\n", p * dx + q * dy);

    long x3, y3;
    if (p <= 0)
        y3 = p + dy, x3 = q;
    else
        x3 = q + dx, y3 = p;
    // printf("(%ld, %ld), (%ld, %ld), (%ld, %ld)\n", 0l, dy, dx, 0l, x3, y3);
    double b = hypot(dx - x3, y3);
    double c = hypot(x3, dy - y3);
    if (a + b + c > maxLength) {
        maxLength = a + b + c;
        ans = a * b * c / 2 / R;
        printf("updated: maxLength = %.6f, ans = %.6f\n", maxLength, ans);
        printf("(%ld, %ld), (%ld, %ld), (%ld, %ld)\n", x1, y1, x2, y2, x3 + x1, y3 + y2);
    }
}

int main() {
    vector<pair<int, int>> points;
    for (long x1 = -R, Y = 0; x1 <= 0; ++x1) {
        if (x1 % 100000 == 0)
            printf("current %ld\n", x1);
        while (Y * Y + x1 * x1 <= R * R)
            ++Y;
        const int T = 3;
        for (long y1 = Y - 1; x1 * x1 + y1 * y1 >= 99999999999000l && x1 * x1 + y1 * y1 <= R * R; --y1) {
            points.push_back({x1, y1});
            continue;
            // for (long x2 = -T - x1; x2 <= T - x1; ++x2)
            //     for (long y2 = -T - y1; y2 <= T - y1; ++y2) {
            //         if (x2 * x2 + y2 * y2 > R * R) continue;
            //     }
        }
    }
    // printf("%d\n", (int) points.size());
    for (auto p1 : points)
        for (auto p2 : points) {
            update(p1.first, p1.second, -p2.first, -p2.second);
        }
    return 0;
}
