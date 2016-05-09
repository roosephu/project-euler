#include <cstdio>
#include <cmath>
using namespace std;

const int n = 10000;

long ans = 0;

long gcd(long a, long b) {
    return a ? gcd(b % a, a) : b;
}

int main() {
    for (long S = 1; S <= n; ++S) {
        if (S % 1000 == 0)
            printf("cur S = %ld\n", S);
        for (long a = 1; a < S; ++a) {
            long t = (S + a) / gcd(a * a, S + a);
            for (long d = t; a + d <= S; d += t) {
                long prod = a * a * d / (S + a), sum = S - a - d;
                long delta = sum * sum - prod * 4;
                if (delta < 0)
                    break;
                long root = sqrt(delta);
                if (root * root == delta) {
                    long b = (sum - root) / 2, c = (sum + root) / 2;
                    // printf("%ld %ld %ld %ld\n", a, b, c, d);
                    ans += S;
                }
            }
        }
    }
    printf("ans = %ld\n", ans);
    return 0;
}
