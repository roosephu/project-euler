#include "fmt/format.h"
#include <map>
#include <vector>
using namespace fmt;
using namespace std;

const int MAX_DEPTH = 66;

long e = 1;
map<vector<long>, long> f[MAX_DEPTH];

vector<long> multiply(vector<long> A, vector<long> B) {
    vector<long> C, ret;
    for (auto x : A)
        for (auto y : B)
            C.push_back(x + y);
    sort(C.begin(), C.end());

    for (int i = 0; i < C.size(); ++i) {
        if (i + 1 < C.size() && C[i] == C[i + 1]) {
            ++i;
        } else {
            ret.push_back(C[i]);
        }
    }
    return ret;
}

long dfs(int depth, vector<long> poly) {
    // print("depth: {} => ", depth);
    // for (auto x : poly)
    //     print("{} ", x);
    // print("\n");

    if (depth == 0)
        return poly.size();
    if (!f[depth].count(poly)) {
        long t = 1ll << depth;
        long last = 0, start = 0, ret = 0;
        vector<long> tmp;
        for (auto x : poly) {
            if (x - last > t * 8) {
                start = x;
                if (tmp.size()) {
                    ret += dfs(depth, vector<long>(tmp));
                    tmp.clear();
                }
            }
            last = x;
            tmp.push_back(x - start);
        }
        if (start != 0) {
            ret += dfs(depth, tmp);
            return ret;
        }

        if ((e & t) == t) {
            vector<long> x;
            for (int i = 0; i <= 4; ++i)
                x.push_back(i * t);
            tmp = multiply(tmp, x);

            // print("y: ");
            // for (auto y : tmp) {
            //     print("{} ", y);
            // }
            // print("\n");
            ret = dfs(depth - 1, tmp);
        } else {
            ret = dfs(depth - 1, tmp);
        }

        f[depth][poly] = ret;
    }
    return f[depth][poly];
}

int main() {
    vector<long> zero;
    zero.push_back(0);

    long ans = 0;
    for (int i = 1; i <= 18; ++i) {
        e *= 10;
        for (int j = 0; j < MAX_DEPTH; ++j)
            f[j].clear();
        long current = dfs(60, zero);
        int hash_size = 0;
        for (int j = 0; j < MAX_DEPTH; ++j)
            hash_size += f[j].size();

        print("e = {}, ans = {}, hash size = {}\n", e, current, hash_size);
        ans += current;
    }
    print("ans = {}\n", ans);
    return 0;
}