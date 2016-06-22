#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

const int n = 43, N = 3e7;
const double inf = 1e300;

int primes[] = {2, 3, 5, 23, 7, 11, 13, 17, 19, 29, 31, 37, 41, 43};
double logP[20];
int cnt[20];
vector<pair<double, double>> pointsL, pointsR;
vector<double> ys;
double bit[N];
int facA[20], facB[20], facC[20];

bool is(double a, double b) {
    return abs(a - b) <= 1e-9;
}

long getV(int *exp, int L, int R) {
    long ret = 1;
    for (int i = L; i <= R; ++i)
        for (int a = 1; a <= exp[i]; ++a)
            ret *= primes[i];
    return ret;
}

void dfs(int dep, double x, double y, double z, int L, int R) {
    if (dep == R) {
        if (R != 4) {
            pointsR.push_back({x - y, y - z});
            if (is(x - y, -17.3362279365) && is(y - z, 13.6710695155))
                printf("find R: (x, y, z) = (%ld, %ld, %ld)\n", getV(facA, L, R), getV(facB, L, R), getV(facC, L, R));
        } else {
            pointsL.push_back({y - x, z - y});
            if (is(y - x, -17.3362285952) && is(z - y, 13.6710656677))
                printf("find L: (x, y, z) = (%ld, %ld, %ld)\n", getV(facA, L, R), getV(facB, L, R), getV(facC, L, R));
        }
        return;
    }
    double p = logP[dep];
    for (int a = 0; a <= cnt[dep]; ++a)
        for (int b = 0; a + b <= cnt[dep]; ++b) {
            facA[dep] = a;
            facB[dep] = b;
            facC[dep] = cnt[dep] - a - b;
            dfs(dep + 1, x + p * a, y + p * b, z + p * (cnt[dep] - a - b), L, R);
        }
}

int getY(double y) {
    return upper_bound(ys.begin(), ys.end(), y) - ys.begin();
}

void insert(int a, double v) {
    for (; a < N; a += a & -a)
        if (bit[a] < v)
            bit[a] = v;
}

double query(int t) {
    double ret = -inf;
    for (; t; t &= t - 1)
        ret = max(ret, bit[t]);
    return ret;
}

int main() {
    for (int i = 0; i < 14; ++i)
        for (int t = n; t /= primes[i]; )
            cnt[i] += t;
    for (int i = 0; i < 14; ++i)
        logP[i] = log(primes[i]);

    // dfs(0, 0, 0, 0, 0, 8);
    // double best = inf;
    // for (auto &it : pointsL) {
    //     if (it.first <= 0 && it.second <= 0) {
    //         // printf("xxx\n");
    //         double cost = it.first + it.second;
    //         if (-cost < best) {
    //             best = -cost;
    //             printf("ans = %.10f, L = %.10f, R = %.10f\n", best, it.first, it.second);
    //         }
    //     }
    // }
    // return 0;

    dfs(0, 0, 0, 0, 0, 4);
    printf("|pointsL| = %d, |pointsR| = %d\n", (int) pointsL.size(), (int) pointsR.size());
    dfs(4, 0, 0, 0, 4, 14);
    printf("|pointsL| = %d, |pointsR| = %d\n", (int) pointsL.size(), (int) pointsR.size());
    sort(pointsL.begin(), pointsL.end());
    sort(pointsR.begin(), pointsR.end());

    for (auto &it : pointsL)
        ys.push_back(it.second);
    sort(ys.begin(), ys.end());

    auto p = pointsR.begin();
    double ans = inf;
    for (int i = 1; i < N; ++i)
        bit[i] = -inf;

    pointsL.push_back({inf, 0});
    for (auto &it : pointsL) {
        for (; p != pointsR.end() && p->first < it.first; ++p) {
            double costL = query(getY(p->second));
            double cost = p->first + p->second - costL;
            if (cost < ans) {
                ans = cost;

                printf("new cost: R = (%.10f, %.10f), costL = %.10f, cost = %.10f\n", p->first, p->second, costL, cost);
            }
        }

        int y = getY(it.second);
        // if (!is(ys[y - 1], it.second)) {
        //     printf("xxx\n");
        // }
        insert(y, it.first + it.second);

        if (is(it.first + it.second, -3.6651629275))
            printf("L pair: %.10f %.10f\n", it.first, it.second);
    }
    printf("Releasing...\n");

    // new cost: R = (-17.3362279365, 13.6710695155), costL = -3.6651629275, cost = 0.0000045065

    return 0;
}
