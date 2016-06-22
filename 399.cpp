#include <cstdio>
#include <NTL/ZZ_p.h>
#include <NTL/matrix.h>
#include <NTL/mat_ZZ_p.h>
#include <cmath>
using namespace std;
using namespace NTL;

#define setbit(x, p) (x[(p) >> 5] |= 1u << ((p) & 31))
#define getbit(x, p) (x[(p) >> 5] >> ((p) & 31) & 1)

const int n = 1e8, N = 1.5e8;
const long MOD = 1e16;

unsigned int mark[N / 32 + 10];

long find(int p, int LMT) {
    int a = 0, b = 1, ret = 1;
    for (; ; ) {
        int c = (a + b) % p;
        a = b;
        b = c;
        if (a == 0 || ret > LMT)
            break;
        ++ret;
    }
    return ret;
}

int main() {
    for (int p = 2; p <= 100000000; ++p)
        if (ProbPrime(p)) {
            long x = find(p, N / p + 10) * p;
            for (long i = x; i <= N; i += x)
                setbit(mark, i);
        }
    int cnt = 0, ans = 0;
    for (int i = 1; i <= N; ++i)
        if (getbit(mark, i) == 0) {
            ++cnt;
            if (cnt == n) {
                ans = i;
                break;
            }
        }
    printf("%d-th: %d\n", cnt, ans);

    // int cnt = 425840376;
    // int cnt = 4;

    ZZ_p::init(ZZ(MOD));
    Mat<ZZ_p> U;
    U.SetDims(2, 2);
    U(1, 1) = U(1, 2) = U(2, 1) = 1;

    power(U, U, ans - 1);
    printf("%ld,", trunc_long(rep(U(1, 1)), 64));

    double num = ans * (log(sqrt(5) + 1) - log(2)) - log(5) / 2;
    double den = log(10);
    printf("%.1fe%d\n", exp(fmod(num, den)), (int) floor(num / den));
    return 0;
}
