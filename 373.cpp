#include <cstdio>
#include <NTL/ZZ.h>
#include <vector>
using namespace std;
using namespace NTL;

const int n = 1e7, N = n + 10;

struct node {
    long x, y, z;
};

vector<node> G[N];

long LCM(long a, long b) {
    return a / GCD(a, b) * b;
}

int main() {
    long s = 0;
    for (long u = 1; u * u <= n; ++u)
        for (long v = 1; v < u && u * u + v * v <= n; ++v)
            if (GCD(u, v) == 1 && (u - v) % 2 != 0) {
                long a = u * u - v * v;
                long b = 2 * u * v;
                long c = u * u + v * v;
                if (c <= n) {
                    ++s;
                    G[c].push_back((node){a, b, c});
                    G[c].push_back((node){b, a, c});
                }
            }

    printf("s = %ld\n", s);
    long ans = 0;

    long cnt = 0, last = 1;
    for (int d = 1; d <= n; ++d) {
        vector<node> F;
        for (int i = 1; i * d <= n; ++i)
            for (auto x : G[i * d])
                F.push_back(x);
        if (d >= last) {
            printf("%d: %d\n", d, (int) F.size());
            last = last * 1.5 + 1;
        }
        for (auto a : F)
            for (auto b : F) {
                if (a.z * b.z > d * n) break;
                long gz = GCD(a.z, b.z);
                if (gz != d) continue;
                long x = a.x * b.z, y = b.x * a.z, z = a.x * b.y + a.y * b.x;
                if (x <= y && y <= z) {
                    long r = a.z * b.z;
                    long g = GCD(GCD(a.z, b.z), z);
                    if (g != 1) {
                        // printf("%ld %ld %ld r = %ld, g = %ld\n", x, y, z, r, g);
                        x /= g, y /= g, z /= g, r /= g;
                    }

                    long m = n / r;
                    if (m > 0) {
                        ans += m * (m + 1) / 2 * r;
                        cnt += 1;
                        // F[r].push_back({x, y, z});
                    }
                }
            }
    }
    // for (int r = 1; r <= n; ++r)
    //     for (auto a : F[r])
    //         printf("d = %d, %ld %ld %ld\n", r, a.x, a.y, a.z);


    printf("ans = %ld, cnt = %ld\n", ans, cnt);
    return 0;
}
