#include <NTL/ZZ.h>
#include "fmt/format.h"
#include <algorithm>
using namespace std;
using namespace fmt;
using namespace NTL;

namespace PE524 {
    const int n = 45;

    int p[n] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 25, 24, 26, 27, 29, 31, 33, 35, 37, 39, 38, 41, 44, 42, 40, 36, 34, 32, 30, 28, 43};
    long store[10];

    long FS(int *p) {
        int mx = -1;
        long ret = 0;
        for (int i = 0; i < n; ++i) {
            if (p[i] > mx) {
                mx = p[i];
            } else {
                int x = 0;
                for (int j = 0; j < i; ++j) {
                    x += p[j] < p[i];
                }
                ret += 1ll << x;
            }
        }
        return ret;
    }

    void gen(long x, int *p) {
        // print("x = {}\n", x);
        int i = 0;
        int t = 0;
        while (x >> i) {
            while (~x >> i & 1) {
                p[t++] = i;
                ++i;
            }
            int cnt = 0, j = i, nz = 0;
            for (; x >> j; ++j) {
                if (x >> j & 1) {
                    ++cnt;
                    ++nz;
                } else {
                    --cnt;
                }
                if (cnt == 0) {
                    ++j;
                    break;
                }
            }
            // print("i = {}, j = {}\n", i, j);
            vector<int> us, vs;
            for (int d = 0; d < j - i - nz; ++d) {
                us.push_back(i + d * 2 + 1);
            }
            if (cnt > 0) {
                us.push_back(j);
            }
            vs.push_back(0);
            for (int d = 0; d < (int)us.size() - 1; ++d) {
                for (int r = us[d] + 1; r < us[d + 1]; ++r) {
                    vs.push_back(r);
                }
            }
            print("us:");
            for (auto u : us) {
                print(" {}", u);
            }
            print("\n");
            print("vs:");
            for (auto v : vs) {
                print(" {}", v);
            }
            print("\n");

            int d = i;
            for (auto v : vs) {
                while (~x >> d & 1) {
                    ++d;
                }
                if (d == i) {
                    us.push_back(i);
                    ++d;
                    continue;
                }
                print("d = {}, v = {}\n", d, v);
                for (int r = 0, find_max = false, c = d - i; r < us.size(); ++r) {
                    if (r < us.size() && us[r] > v) {
                        find_max = true;
                    }
                    if (us[r] < v) {
                        --c;
                    }
                    if (find_max && c == 0) {
                        // print("insert pos: {}\n", r + 1);
                        us.insert(us.begin() + r + 1, v);
                        break;
                    }
                }
                ++d;

                // print("us:");
                // for (auto u : us) {
                //     print(" {}", u);
                // }
                // print("\n");
            }
            for (auto u : us) {
                p[t++] = u;
            }
            i = j;
        }
    }

    long perm_index(int *p) {
        long ret = 1;
        for (int i = 0; i < n; ++i) {
            long t = p[i];
            for (int j = 0; j < i; ++j) {
                t -= p[j] < p[i];
            }
            for (int j = 1; i + j < n; ++j) {
                t *= j;
            }
            ret += t;
        }
        return ret;
    }

    void main() {
        print("FS: {}\n", perm_index(p));
        return;
        gen(39, p);
        print("p:");
        for (int i = 0; i < n; ++i) {
            print(" {}", p[i]);
        }
        print("\n");
        return;
        for (int i = 0; i < n; ++i) {
            p[i] = i;
        }

        int idx = 0;
        do {
            long t = FS(p);
            idx += 1;
            if (store[t] == 0) {
                store[t] = idx;
                // if (t == 11) {
                    print("target {0:3d} {0:09b}:", t);
                    for (int i = 0; i < n; ++i) {
                        print(" {}", p[i]);
                    }
                    print("\n");
                // }
            }
            assert(perm_index(p) == idx);
        } while (next_permutation(p, p + n));

        for (int i = (1 << (n - 2)); i < (1 << (n - 1)); ++i) {
            gen(i, p);
            if (perm_index(p) != store[i]) {
                print("x {0} {0:b}:", i);
                for (int t = 0; t < n; ++t) {
                    print(" {}", p[t]);
                }
                print("\n");
            } else {
                print("  {0} {0:b}\n", i);
            }
        }
    }
}

int main() {
    PE524::main();
    return 0;
}
