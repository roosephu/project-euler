#include "fmt/format.h"
using namespace fmt;

const long inf = 1e18;
const int N = 2000000;

int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};
long st[32], base = 16;
long values[N], *pointers[16];

int main() {
    int m = 15;
    values[0] = 1;
    for (int i = 0; i < 16; ++i) {
        pointers[i] = values;
        // if (i >= m)
        //     modify(i, inf);
        // else
        //     modify(i, *pointers[i] * primes[i]);
    }

    long last = 1, sum = 0;
    for (int i = 1; i < N; ++i) {
        long min_val = inf, src = -1;
        for (int j = 0; j < m; ++j) {
            long v = *pointers[j] * primes[j];
            if (v < min_val) {
                min_val = v;
                src = j;
            }
        }
        for (int j = 0; j < m; ++j) {
            long v = *pointers[j] * primes[j];
            if (v == min_val) {
                ++pointers[j];
            }
        }

        values[i] = min_val;
        if (min_val == last + 1) {
            sum += last;
            print("# {}: last = {}, sum = {}\n", i, last, sum);
        }
        last = min_val;
        // if (i % 1000000 == 0)
        //     print("{}\n", min_val);
    }
    return 0;
}