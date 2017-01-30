#include "fmt/format.h"
#include <cmath>
using namespace fmt;
using namespace std;

int main() {
    double pi = acos(-1);
    for (int n = 1; n <= 2244; ++n) {
        double k = 1. / n;
        double x = (k + 1 - sqrt(2 * k)) / (k * k + 1);
        double y = k * x;
        double theta = asin(1 - x);
        double area = y * x / 2 + (y + 1) * (1 - x) / 2 - theta / 2;
        double ratio = area / (1 - pi / 4);
        print("n = {}, ratio = {:.9f}, x = {}, y = {}, theta = {}\n", n, ratio, x, y, theta);
    }
    return 0;
}