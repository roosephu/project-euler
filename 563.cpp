#include <cstdio>
#include <cmath>
#include <vector>
using namespace std;

const long LMT = 2293751652192000l, m = 100, M = m + 10;

int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23};
vector<long> candidates;
int found[M];

void dfs(long dep, long cur) {
    if (dep < 0) {
        candidates.push_back(cur);
        return;
    }
    for (; cur <= LMT; ) {
        dfs(dep - 1, cur);
        cur *= primes[dep];
    }
}

int main() {
    dfs(8, 1);
    printf("%d\n", (int) candidates.size());
    sort(candidates.begin(), candidates.end());

    long ans = 0;
    int completed = 0;
    for (auto x : candidates) {
        if (x == 1)
            continue;
        auto fst = lower_bound(candidates.begin(), candidates.end(), sqrt(x * 10. / 11));
        int cnt = 0;

        while (*fst * *fst * 11 < x * 10)
            ++fst;
        for (; *fst * *fst <= x; ++fst) {
            if (x % *fst == 0) {
                ++cnt;
            }
        }

        if (!found[cnt] && 2 <= cnt && cnt <= m) {
            found[cnt] = true;
            ++completed;
            printf("%d(%d): %ld\n", cnt, completed, x);
            ans += x;
            if (completed == m - 1)
                break;
        }
    }
    printf("%ld\n", ans);
    return 0;
}
