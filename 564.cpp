#include <cstdio>
#include <cmath>
using namespace std;

const int N = 55, ITER = 50;
const double pi = acos(-1), eps = 1e-14;

int len[N];
int n;
// int cnt = 0;
double ans = 0;
double sum_ans = 0;
double sum_weight = 0;

double get_angles(double diam) {
    double angles = 0;
    for (int i = 1; i <= n; ++i)
        angles += asin(len[i] / diam);
    return angles;
}

double compute() {
    double L = len[1], R = 2 * n - 3, m;
    if (get_angles(L) < pi) {
        len[1] = -len[1];
        for (int i = 1; m = (L + R) / 2, i <= ITER; ++i) {
            double angles = get_angles(m);
            if (angles <= 0)
                L = m;
            else
                R = m;
        }
    } else {
        for (int i = 1; m = (L + R) / 2, i <= ITER; ++i) {
            double angles = get_angles(m);
            if (angles > pi)
                L = m;
            else
                R = m;
        }
    }

    double area = 0;
    for (int i = 1; i <= n; ++i) {
        area += sqrt(m * m - len[i] * len[i]) * len[i];
    }
    // for (int i = 1; i <= n; ++i) {
    //     printf("%d ", len[i]);
    // }
    // printf(": diam = %.3f, area = %.3f\n", m, area);

    if (len[1] < 0)
        len[1] = -len[1];
    return area / 4;
}

void dfs(int dep, int sum, int last) {
    if (dep > n) {
        double cur = compute();
        double weight = 1;
        for (int i = 1, j = 0; i <= n; ++i) {
            if (len[i] == len[i - 1])
                ++j;
            else
                j = 1;
            weight /= j;
        }
        // weight = 1 - weight;
        sum_weight += weight;
        sum_ans += cur * weight;
        // printf("%.6f %.6f\n", weight, cur);
        // ++cnt;
        return;
    }
    int rem = n - dep + 1;
    if (sum < rem || rem * last < sum)
        return;
    for (int i = 1; i <= last && i <= sum; ++i) {
        len[dep] = i;
        dfs(dep + 1, sum - i, i);
    }
}

int main() {
    for (n = 3; n <= 50; ++n) {
        // cnt = 0;
        sum_ans = 0;
        sum_weight = 0;
        dfs(1, 2 * n - 3, n);
        double cur_ans = sum_ans / sum_weight;
        ans += cur_ans;
        printf("%d: %.6f\n", n, ans);
        // printf("%d: %d\n", n, cnt);
    }
    return 0;
}
