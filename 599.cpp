#include "fmt/format.h"
#include <set>
#include <map>
#include <queue>
#include <cassert>
using namespace fmt;
using namespace std;

namespace PE599 {
    const int N = 4e6, TOTAL = 3674160 * 24, m = 10;

    int cycles[30] = {0, 0, 19053144, 17404632, 3289734, 19675656, 13976640, 1591128, 6753434, 4262412, 261156, 1076040, 664825, 17640, 87500, 58800, 420, 3528, 3010, 0, 56, 84, 0, 0, 1};

    struct perm {
        int v[24];
    };

    int fs[][3] = {
        {0, 1, 2},
        {1, 2, 0},
        {2, 0, 1},
        {3, 1, 0},
        {4, 0, 2},
        {5, 2, 1},
    };

    bool operator < (perm a, perm b) {
        for (int i = 0; i < 24; ++i)
            if (a.v[i] != b.v[i])
                return a.v[i] < b.v[i];
        return false;
    }

    perm operator + (perm a, perm b) {
        perm c;
        for (int i = 0; i < 24; ++i) {
            c.v[i] = b.v[a.v[i]];
        }
        return c;
    }

    set<perm> S;
    map<int, int> F;
    perm B[24], Q[N], A[6];
    int L = 1, R = 0;

    int find(int a, int b, int c) {
        if (b > c) swap(b, c);
        int S = a * 100 + b * 10 + c;
        if (!F.count(S)) {
            int x = F.size();
            F[S] = x;
        }
        return F[S];
    }

    int inverse(perm x) {
        int inv = 0;
        for (int i = 0; i < 24; ++i) {
            for (int j = i + 1; j < 24; ++j) {
                inv += x.v[i] > x.v[j];
            }
        }
        return inv;
    }

    bool push(perm x) {
        if (S.count(x) == 0) {
            assert(R < N);
            Q[++R] = x;
            S.insert(x);
            return true;
        }
        return false;
    }

    int cycle(perm x) {
        bool o[24] = {0};
        int ret = 0;
        for (int i = 0; i < 24; ++i) {
            if (!o[i]) {
                ++ret;
                while (!o[i]) {
                    o[i] = true;
                    i = x.v[i];
                }
            }
        }
        if (ret == 0 || ret > 24)
            print("xxx\n");
        return ret;
    }

    void init() {
        for (int a = 0; a < 6; ++a) {
            int b = fs[a][1], c = fs[a][2];
            int seq[] = {b, c, 5 - b, 5 - c, b, c};

            perm x;
            for (int i = 0; i < 24; ++i)
                x.v[i] = i;
            for (int i = 0; i < 4; ++i) {
                x.v[find(a, seq[i], seq[i + 1])] = find(a, seq[i + 1], seq[i + 2]);
                x.v[find(seq[i], seq[i + 1], a)] = find(seq[i + 1], seq[i + 2], a);
                x.v[find(seq[i + 1], a, seq[i])] = find(seq[i + 2], a, seq[i + 1]);
            }
            B[2 * a] = x;

            for (int i = 0; i < 24; ++i)
                B[2 * a + 1].v[x.v[i]] = i;
        }
        perm identity;
        for (int i = 0; i < 24; ++i)
            identity.v[i] = i;
        push(identity);
        for (int i = 0; i < 6; ++i)
            A[i] = B[2 * i] + B[11 - 2 * i];

        set<perm> faces;
        for (int i = 0; i < 6; ++i) {
            faces.insert(A[i]);
            for (int j = 0; j < 6; ++j) {
                faces.insert(A[i]  + A[j]);
                for (int k = 0; k < 6; ++k) {
                    faces.insert(A[i]  + A[j] + A[k]);
                }
            }
        }
        print("|faces| = {}\n", faces.size());

        int cycles[50] = {0};
        for (; L <= R; ++L) {
            if (L % 10000 == 0)
                print("L = {}, R = {}\n", L, R);
            auto &x = Q[L];

            for (int idx = 0; idx < 6; ++idx) {
                push(B[idx] + x);
            }

            for (auto p : faces) {
                ++cycles[cycle(p + x)];
            }
        }
        for (int i = 1; i < 50; ++i) {
            print("{}\n", cycles[i]);
        }

        // long ans = 0;
        // for (int i = 1; i <= 50; ++i) {
        //     if (cycles[i]) {
        //         ans += (long) PowerMod(m, i) * cycles[i];
        //     }
        // }
    }

    void main() {
        // init();
        long ans = 0, power = 1;
        for (int i = 0; i < 30; ++i) {
            ans += power * cycles[i];
            power *= m;
        }
        print("ans = {}, {}\n", ans / TOTAL, ans % TOTAL);
    }
}

int main() {
    PE599::main();
    return 0;
}