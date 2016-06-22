#include <cstdio>
using namespace std;

const int m = 904961;

long fpm(long b, long e, long m) {
    long t = 1;
    for (; e; e >>= 1, b = b * b % m)
        e & 1 ? t = t * b % m : 0;
    return t;
}

// S(m, n) = (n + 2)^m - 2^m

int main() {
    for (int i = 1; i <= 100; ++i) {
        int k = 0;
        while (fpm(i + 2))
    }
    return 0;
}
