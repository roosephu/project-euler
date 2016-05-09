#include <cstdio>
#include <vector>
using namespace std;

const long n = 1e12;
const int N = 1e6 + 10;

int primes[N + 10];
vector<int> cs[N + 10];
long ans = 0;
int mark[N + 10];

long gcd(long a, long b) {
    return a ? gcd(b % a, a) : b;
}

long lcm(long a, long b) {
    long g = gcd(a, b);
    return a / g * b;
}

long phi(long m) {
    long ret = m;
    for (int i = 1; (long)primes[i] * primes[i] <= m; ++i) {
        if (m % primes[i] == 0) {
            ret = ret / m * (m - 1);
            while (m % primes[i] == 0)
                m /= primes[i];
        }
    }
    if (m > 1)
        ret = ret / m * (m - 1);
    return ret;
}

long mul(long a, long b, long m) {
    long ret = a * b - (long)((long double)a * b / m) * m;
    while (ret < 0)
        ret += m;
    while (ret >= m)
        ret -= m;
    return ret;
}

long fpm(long b, long e, long m) {
    long t = 1;
    for (; e; e >>= 1, b = mul(b, b, m))
        e & 1 ? t = mul(t, b, m) : 0;
    return t;
}

int cnt = 0;

void analyse(long m) {
    printf("%d, %ld: ", cnt, m);
    // for (int i = 1; (long)primes[i] * primes[i] <= m; ++i) {
    //     if (m % primes[i] == 0) {
    //         m /= primes[i];
    //         printf(" %d", primes[i] % 3);
    //     }
    // }
    // if (m != 1)
    //     printf(" %ld", m % 3);
    printf("\n");
}

int check = 0;
void dfs(int dep, long l, long m) {
    if (l > n || m > n)
        return;
    // if (m > 100000) {
    //     long lim = mul(l - 3, fpm(m, phi(l) - 1, m), l);
    //     ++check;
    //     if (lim > n / m) {
    //         printf("hit! check = %d\n", check);
    //     }
    // }
    if ((m + 3) % l == 0) {
        cnt += 1;
        // printf("%d: %ld\n", cnt, m);
        analyse(m);
        ans += m;
    }

    for (; dep <= primes[0] && m <= n / primes[dep]; ++dep) {
        int p = primes[dep];
        for (auto x : cs[dep])
            if (m % x == 0)
                continue;
        long newL = lcm(l, p - 1);
        if (newL > n)
            continue;

        dfs(dep + 1, newL, m * p);
    }
}

int main() {
    for (int i = 2; i <= N; ++i) {
        if (!primes[i]) primes[++primes[0]] = i;
        for (int j = 1, k = N / i; primes[j] <= k; ++j) {
            int t = i * primes[j]; primes[t] = 1;
            if (i % primes[j] == 0) break;
        }
    }
    for (int i = 1; i <= primes[0]; ++i) {
        int t = primes[i] - 1;
        for (int x = 1; primes[x] * primes[x] <= t; ++x)
            if (t % primes[x] == 0) {
                if (primes[x] != 3)
                    cs[i].push_back(primes[x]);
                while (t % primes[x] == 0)
                    t /= primes[x];
            }
        if (t > 1 && t != 3)
            cs[i].push_back(t);
    }

    ans += 2;
    dfs(2, 1, 1); // do not search prime 2
    printf("ans = %ld\n", ans);

    return 0;
}
