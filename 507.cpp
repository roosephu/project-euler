#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;

const int MOD = 1e7;

struct vector {
    long a, b, c;
};

int t0 = 0, t1 = 0, t2 = 1;

long R() {
    int t3 = (t0 + t1 + t2) % MOD;
    t0 = t1;
    t1 = t2;
    t2 = t3;
    return t0;
}

vector next_vec() {
    return (vector){R() - R(), R() + R(), R() * R()};
}

long abs(long t) {
    return t >= 0 ? t : -t;
}

long norm(vector x) {
    return abs(x.a) + abs(x.b) + abs(x.c);
}

int main() {
    long ans = 0;
    for (int t = 1; t <= 20000000; ++t) {
        if (t % 100000 == 0) {
            printf("%d\n", t);
        }
        vector a = next_vec(), b = next_vec();

        for (int i = 0; i < 500; ++i) {
            double r = (double)a.a * b.a + (double)a.b * b.b + (double)a.c * b.c;
            r /= (double)b.a * b.a + (double)b.b * b.b + (double)b.c * b.c;
            long c = round(r);
            a.a -= c * b.a;
            a.b -= c * b.b;
            a.c -= c * b.c;

            vector T = a;
            a = b;
            b = T;
        }

        long cur = min(norm(a), norm(b));
        ans += cur;
        // printf("cur: %ld\n", cur);
    }
    printf("%ld\n", ans);
    return 0;
}
