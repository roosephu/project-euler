#include <cstdio>
#include <vector>
#include <cmath>
using namespace std;

struct node {
    double x1, y1;
    double x2, y2;
};

vector<node> P, Q;
double xmax = 1, ymax = 0, xmin = 0, ymin = -1;

int main() {
    P.push_back({0, 0, 1, 0});
    for (int i = 1; i < 100; ++i) {
        Q.clear();
        for (auto x : P) {
            xmax = max(xmax, max(x.x1, x.x2));
            xmin = min(xmin, min(x.x1, x.x2));
            ymax = max(ymax, max(x.y1, x.y2));
            ymin = min(ymin, min(x.y1, x.y2));

            double dx = x.x2 - x.x1;
            double dy = x.y2 - x.y1;

            // node z = (node){
            //     x.x1 - 5 * dx - 5 * dy, x.y1 + 5 * dx - 5 * dy,
            //     x.x1 - 5 * dx + 2 * dy, x.y1 - 2 * dx - 5 * dy,
            //     x.x1 + 5 * dx - 5 * dy, x.y1 + 5 * dx + 5 * dy,
            //     x.x1 + 5 * dx + 2 * dy, x.y1 - 2 * dx + 5 * dy
            // };
            if (xmin <= x.x1 + min(5 * dx, -5 * dx) + min(-5 * dy, 2 * dy) &&
                xmax >= x.x1 + max(5 * dx, -5 * dx) + max(-5 * dy, 2 * dy) &&
                ymin <= x.y1 + min(5 * dx, -2 * dx) + min(-5 * dy, 5 * dy) &&
                ymax >= x.y1 + max(5 * dx, -2 * dx) + max(-5 * dy, 5 * dy))
                continue;

            node y1 = (node){
                x.x1 - 0.48 * dx - 0.64 * dy, x.y1 + 0.64 * dx - 0.48 * dy,
                x.x1 + 0.16 * dx - 1.12 * dy, x.y1 + 1.12 * dx + 0.16 * dy
            };
            node y2 = (node){
                x.x1 + 1.12 * dx - 0.84 * dy, x.y1 + 0.84 * dx + 1.12 * dy,
                x.x1 + 1.48 * dx - 0.36 * dy, x.y1 + 0.36 * dx + 1.48 * dy,
            };
            Q.push_back(y1);
            Q.push_back(y2);
            // printf("%.3f => %.3f %.3f\n", hypot(dx, dy), hypot(y1.x1 - y1.x2, y1.y1 - y1.y2), hypot(y2.x1 - y2.x2, y2.y1 - y2.y2));
        }
        P = Q;
        printf("%d\n", (int) Q.size());
        printf("ans = %.10f\n", (xmax - xmin) * (ymax - ymin));
    }
    printf("xmax = %.6f, ymax = %.6f, xmin = %.6f, ymin = %.6f\n", xmax, ymax, xmin, ymin);
    return 0;
}
