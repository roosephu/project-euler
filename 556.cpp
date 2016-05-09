#include <cstdio>
#include <cmath>
#include <map>
using namespace std;

const long n = 1e14, L = 1e7;

map<long, long> _f, _g;
long _F[L + 2];

long f(long t) {
    if (t <= L)
        return _F[t];
    if (!_f.count(t)) {
        long x = 0;
        for (long i = 1, j = sqrt(t); i * i <= t; ++i) {
            for (; i * i + j * j > t; )
                --j;
            x += j + 1;
        }
        _f[t] = x;
    }
    return _f[t];
}

long h(long t) {
    return f(t) - f(t - 1);
}

long g(long t) {
    if (!_g.count(t)) {
        long x = f(t);
        for (long i = 2; i * i <= t; ++i) {
            x -= g(t / i / i) * h(i);
        }
        _g[t] = x;
    }
    return _g[t];
}

int main() {
    for (int i = 1; i * i <= L; ++i)
        for (int j = 0; i * i + j * j <= L; ++j)
            ++_F[i * i + j * j];
    for (int i = 1; i <= L; ++i)
        _F[i] += _F[i - 1];
    // printf("f(n) = %ld, F(n) = %ld\n", f(1e7), _F[(int)1e7]);
    printf("ans = %ld\n", g(n));
    printf("resource: f.size = %d, g.size = %d\n", (int)_f.size(), (int)_g.size());
    return 0;
}
