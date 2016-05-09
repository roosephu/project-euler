#include <cstdio>
#include <cmath>
#include <map>
using namespace std;

const long n = 3141592653589793l, N = (long) 7e7 | 1;
// const long n = 1e6, N = 1010;

long S(long x) {
    long ret = sqrt(x);
    while (ret * ret > x)
        ret -= 1;
    while ((ret + 1) * (ret + 1) <= x)
        ret += 1;
    return ret;
}

long solve(long n) {
    static map<long, long> f;
    if (!f.count(n)) {
        long ret = 0;
        for (long u = 1; u * u <= n; u += 2)
            ret += S(n - u * u) / 2;
        f[n] = ret;
        // printf("f[%ld]: %ld\n", n, ret);
    }
    return f[n];
}

long f[N + 10];

int main() {
    for (int i = N; i > 0; i -= 2) {
        f[i] = solve(n / i / i);
        for (int j = 3; i * j <= N; j += 2)
            f[i] -= f[i * j];
    }
    printf("%ld\n", f[1]);
    return 0;
}
