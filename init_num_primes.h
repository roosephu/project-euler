#include <NTL/ZZ.h>
#include <functional>
#include <vector>
#include <map>
using namespace NTL;
using namespace std;

// long basis[M];
map<long, long> dvs;

// void init_num_primes(int n) {
//     long R = SqrRoot(n);
//     int cnt = 0;
//     for (long i = 1; n / i > R; ++i)
//         basis[++cnt] = n / i;
//     for (int i = R; i; --i)
//         basis[++cnt] = i;

//     for (int i = 1; i <= cnt; ++i) {
//         long x = basis[i];
//         dvs[x] = x - 1;
//     }
//     for (long x = 2; x <= R; ++x) {
//         if (ProbPrime(x)) {
//             for (int i = 1; i <= cnt; ++i) {
//                 long y = basis[i];
//                 if (x * x > y)
//                     break;
//                 auto a = dvs[y / x];
//                 auto b = dvs[x - 1];
//                 dvs[y] -= a - b;
//             }
//         }
//     }
// }

tuple<vector<long>, vector<long>, function<int (long)>> sum_of_prime_func(long n, function<long (long)> f, function<long (long)> F) {
    long R = SqrRoot(n);
    vector<long> basis;
    vector<long> ret;
    for (int i = 1; n / i > R; ++i)
        basis.push_back(n / i);
    for (int i = R; i; --i)
        basis.push_back(i);
    for (auto x : basis)
        ret.push_back(F(x));

    int size = basis.size();
    auto get_index = [=](long t) {
        return (t <= R ? size - t : n / t) - 1;
    };

    for (long x = 2; x <= R; ++x) {
        if (!ProbPrime(x)) continue;
        for (auto y : basis) {
            if (x * x > y) break;
            auto a = ret[get_index(y / x)];
            auto b = ret[get_index(x - 1)];
            ret[get_index(y)] -= a - b;
        }
    }
    return {ret, basis, get_index};
}
