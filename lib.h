#pragma once
#include <NTL/ZZ.h>
#include <functional>
#include <vector>
#include <map>
#include <set>
#include <tuple>
#include <algorithm>
#include "fmt/format.h"
#include "fmt/ostream.h"
using namespace NTL;
using namespace std;
using namespace fmt;

template<class T>
tuple<vector<long>, vector<T>, function<int (long)>> sum_of_prime_func(
    long n,
    function<T (long)> f,
    function<T (long)> F
) {
    long R = SqrRoot(n);
    vector<long> basis;
    vector<T> ret;
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

vector<int> sieve(int n) {
    vector<int> primes;
    vector<int> test(n + 1);
    for (int i = 2; i <= n; ++i) {
        if (!test[i]) {
            primes.push_back(i);
        }
        for (auto p : primes) {
            if (p * i > n) break;
            long t = i * p;
            test[t] = 1;
            if (i % p == 0) {
                break;
            }
        }
    }
    return primes;
}

template<class T>
vector<T> init_mul_func2(
    int n,
    vector<int> &primes,
    function<T (int)> init,
    function<T (vector<T> &, int, int)> mul
) {
    vector<T> ret(n + 1);
    ret[1] = 1;
    for (auto p : primes)
        ret[p] = init(p);
    for (int i = 2; i <= n; ++i) {
        for (auto p : primes) {
            if (p * i > n) break;
            long t = i * p;
            ret[t] = mul(ret, i, p);
            if (i % p == 0) {
                break;
            }
        }
    }
    return ret;
}

template<class T>
vector<T> init_mul_func(
    int n,
    vector<int> &primes,
    function<T (int, int)> init
) {
    vector<T> f(n + 1);
    f[1] = 1;
    for (auto p : primes) {
        for (long x = p, e = 1; x <= n; x *= p, ++e) {
            f[x] = init(p, e);
        }
    }
    for (int i = 2; i <= n; ++i) {
        for (auto p : primes) {
            if (p * i > n) break;
            long t = i * p, d = i, e = 1;
            for (; d % p == 0; d /= p)
                ++e;
            f[t] = f[d] * f[t / d];
            if (d != i) break;
        }
    }
    return f;
}
