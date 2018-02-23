#pragma once
#include <NTL/ZZ.h>
#include <functional>
#include <vector>
#include <map>
#include <set>
#include <tuple>
#include "fmt/format.h"
#include "fmt/ostream.h"
using namespace NTL;
using namespace std;
using namespace fmt;

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
        return t <= R ? size - t : n / t - 1;
    };

    for (long x = 2; x <= R; ++x) {
        if (!ProbPrime(x)) continue;
        auto fx = f(x);
        auto Tx = ret[get_index(x - 1)];
        for (auto y : basis) {
            if (x * x > y) break;
            auto a = ret[get_index(y / x)];
            ret[get_index(y)] -= fx * (a - Tx);
        }
    }
    return {ret, basis, get_index};
}

// template<class T> vector<T> sieve(int n) {
//     vector<int> primes(n + 1);
//     vector<T> ret(n + 1);
//     int top = 1;
//     for (int i = 2; i <= n; ++i) {
//         if (!primes[i]) {
//             primes[++top] = 1;
//             ret[i] = ..?;
//         }
//         for (int j = 1, limit = n / i; primes[j] <= limit; ++j) {
//             long t = i * primes[j];
//             primes[t] = 1;
//             if (i % primes[j] == 0) {
//                 ret[t] = merge(ret, i, j);
//                 break;
//             } else { // multiplicative
//                 ret[t] = merge2(ret, i, j);
//             }
//         }
//     }
// }
