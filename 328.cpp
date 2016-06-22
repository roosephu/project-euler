#include <cstdio>
#include <algorithm>
#include <deque>
#include <map>
#include <string>
using namespace std;

#define fst first
#define snd second

const int inf = 1e9;
const int n = 200000, N = n + 10;

// int f[N][N], d[N][N], dep[N][N];
// deque<pair<int, int>> Q[N], X;
int log[N];
int dp[N], valid[N];

void push(deque<pair<int, int>> &Q, pair<int, int> v) {
    while (!Q.empty() && Q.back() > v) {
        Q.pop_back();
    }
    Q.push_back(v);
}

string format(int i) {
    char buf[100];
    sprintf(buf, "%d", i);
    return buf;
}

// string show(int L, int R) {
//     if (L > R)
//         return "";
//     if (R - L + 1 == (2 << dep[L][R]) - 1)
//         return "full(" + format(dep[L][R] + 1) + ")";
//     int t = d[L][R];
//     // printf("%d %d %d\n", L, R, t);
//     string ret = "x";
//     if (L < t)
//         ret = "[" + show(L, t - 1) + "]<-" + ret;
//     if (t < R)
//         ret = ret + "->[" + show(t + 1, R) + "]";
//     return ret;
// }

int dfs(int n, int S) {
    if (S <= 1)
        return 0;
    // printf("dfs %d %d\n", n, S);
    int h = log[S];
    if (S == (2 << h) - 1)
        return 2 * ((h - 1) * (1 << h) + 1) + h * n;

    int L = 0, R = 0;
    if (S >= ((1 << h) | (1 << (h - 1)))) { // 11...
        L = (1 << h) - 1;
        R = S - 1 - L;
    } else {
        R = (1 << (h - 1)) - 1;
        L = S - 1 - R;
    }

    int l = dfs(n, L), r = dfs(n + L + 1, R);
    return max(l, r) + n + L + 1;
}

// optimization: a tree can contains only height h and h+1
//   compute the longest path in height h and h+1
//   so given n we can know the longest path
bool dfs2(int S) {
    if (S <= 1)
        return false;
    // printf("dfs %d %d\n", n, S);
    int h = log[S];
    if (S == (2 << h) - 1)
        return h >= 2;

    int L = 0, R = 0;
    if (S >= ((1 << h) | (1 << (h - 1)))) { // 11...
        L = (1 << h) - 1;
        R = S - 1 - L;
    } else {
        R = (1 << (h - 1)) - 1;
        L = S - 1 - R;
    }

    return dfs2(L) && dfs2(R);
}

int main() {
    for (int i = 2; i <= n; ++i)
        log[i] = log[i / 2] + 1;
    // printf("%d\n", dfs(3, 3));
    dp[1] = 0;
    for (int i = 1; i <= n; ++i)
        valid[i] = dfs2(i);

    int last = 0;
    for (int i = 2; i <= n; ++i) {
        dp[i] = inf;
        int opt = 0;
        for (int k = max(0, (int)(0.8 * i - 20)); k < i; ++k) {
            if (i > 100 && !valid[i - 1 - k])
                continue;
            int cost = k + 1 + max(dp[k], dfs(k + 1, i - 1 - k));
            if (cost < dp[i]) {
                dp[i] = cost;
                opt = k;
            }
        }
        // if (last != opt - 1 && i > 10)
        //     printf("%d: %d, %.3f\n", i, opt, 1. * opt / i);
        last = opt;
    }

    // for (int i = n; i; --i)
    //     for (int j = i + 1; j <= n; ++j) {
    //         f[i][j] = inf;
    //         for (int k = i; k <= j; ++k)
    //             f[i][j] = min(f[i][j], k + max(f[i][k - 1], f[k + 1][j]));
    //     }
    // for (int i = 1; i <= 30; ++i) {
    //     for (int j = 1; i + j <= n; ++j) {
    //         printf("len = %d: start = %d, diff = %d\n", i, j, f[j][j + i] - j * (log[i + 1]));
    //     }
    // }

    // int max_size = 0;
    // string last_struct = "";
    // for (int i = n; i; --i) {
    //     d[i][i] = i;
    //     X.clear();
    //     map<int, int> visited;
    //     for (int j = i + 1; j <= n; ++j) {
    //         int o = 0;
    //         f[i][j] = inf;

    //         push(Q[j], make_pair(i + f[i + 1][j], i)); // f[i + 1] here, O(n)
    //         for (; !Q[j].empty(); ) {
    //             auto it = Q[j].front();
    //             int v = it.fst, k = it.snd;
    //             if (visited[k] < j)
    //                 visited[k] = j;
    //             if (f[i][k - 1] > f[k + 1][j]) // f[i] and f[k + 1]
    //                 Q[j].pop_front();
    //             else {
    //                 if (v < f[i][j]) {
    //                     o = k;
    //                     f[i][j] = v; // v = k + f[k + 1][j]
    //                     d[i][j] = o;
    //                 }
    //                 break;
    //             }
    //         }

    //         push(X, make_pair(j + f[i][j - 1], j));
    //         for (; !X.empty(); ) {
    //             auto it = X.front();
    //             int v = it.fst, k = it.snd;
    //             if (visited[k] < j)
    //                 visited[k] = j;
    //             if (f[i][k - 1] < f[k + 1][j]) // f[k + 1]
    //                 X.pop_front();
    //             else {
    //                 // if (i == 1)
    //                 //     printf("j = %d, start = %d, len = %d\n", j, k + 1, j - k);
    //                 if (v < f[i][j]) {
    //                     o = k;
    //                     f[i][j] = v; // v = k + f[i][k - 1]
    //                     d[i][j] = o;
    //                 }
    //                 break;
    //             }
    //         }

    //         dep[i][j] = max(dep[i][o - 1], dep[o + 1][j]) + 1;
    //         // show(o + 1, j); // .c_str();
    //         if (i == 1) {
    //             // string now_struct = show(o + 1, j);
    //             // if (now_struct != last_struct) {
    //             //     last_struct = now_struct;
    //             //     printf("end = %d, opt = %d, len = %d, struct = %s\n", j, o, j - o, show(o + 1, j).c_str());
    //             // }
    //         }
    //     }

    //     int size = 0;
    //     for (int j = i; j <= n; ++j)
    //         size += Q[j].size();
    //     // printf("size: %d\n", size);

    //     int total_visited = 0;
    //     for (auto it : visited)
    //         total_visited += it.snd - it.fst + 1;
    //     // printf("total visited: %d, used k: %d\n", total_visited, (int) visited.size());
    //     if (size > max_size)
    //         max_size = size;

    // }

    // printf("max_size: %d\n", max_size);
    long ans = 0;
    for (int i = 1; i <= n; ++i) {
        ans += dp[i]; // f[1][i];
        // printf("%d: bf = %d, dp = %d\n", i, f[1][i], dp[i]);
    }
    printf("ans = %ld\n", ans);
    return 0;
}
