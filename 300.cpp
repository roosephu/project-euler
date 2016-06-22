#include <cstdio>
#include <vector>
using namespace std;

const int n = 15;

struct node {
    int v[n][3];
};

int G[40][40];
int cnt = 0;
vector<node> states;
int v[20][3];

void push(int x, int u) {
    if (x != u + 1 && x != 0) {
        if (v[u - 1][0] == 0)
            v[u - 1][0] = x;
        else if (v[u - 1][1] == 0)
            v[u - 1][1] = x;
        else
            v[u - 1][2] = x;
    }
}

bool check(node a, node b) {
    for (int i = 0; i < n; ++i) {
        int x = a.v[i][0], y = a.v[i][1], z = a.v[i][2];
        int p = b.v[i][0], q = b.v[i][1], r = b.v[i][2];
        if (p && p != x && p != y && p != z)
            return false;
        if (q && q != x && q != y && q != z)
            return false;
        if (r && r != x && r != y && r != z)
            return false;
    }
    return true;
}

void dfs(int x, int y, int d) {
    if (G[x][y] != 0)
        return;

    v[d - 1][0] = v[d - 1][1] = v[d - 1][2] = 0;
    push(G[x - 1][y], d);
    push(G[x][y - 1], d);
    push(G[x + 1][y], d);
    push(G[x][y + 1], d);
    if (d == 1) {
        ++cnt;
        if (cnt % 100000 == 0)
            printf("cnt: %d, |states| = %d\n", cnt, (int) states.size());
        node x;
        for (int i = 0; i < n; ++i) {
            x.v[i][0] = v[i][0];
            x.v[i][1] = v[i][1];
            x.v[i][2] = v[i][2];
        }
        bool b = true;
        for (auto it = states.begin(); it != states.end(); ++it) {
            if (check(*it, x)) {
                b = false;
                break;
            } else if (check(x, *it)) {
                *it = *states.rbegin();
                states.pop_back();
                if (it == states.end())
                    break;
            }
        }
        if (b) {
            states.push_back(x);
        }
        return;
    }
    G[x][y] = d;

    dfs(x - 1, y, d - 1);
    dfs(x, y - 1, d - 1);
    dfs(x + 1, y, d - 1);
    dfs(x, y + 1, d - 1);
    G[x][y] = 0;
}

int main() {
    dfs(20, 20, n);
    printf("cnt: %d, |states| = %d\n", cnt, (int) states.size());
    // for (auto &x : states) {
    //     printf("---\n");
    //     for (int i = 0; i < n; ++i)
    //         printf("%d %d\n", x.v[i][0], x.v[i][1]);
    // }

    double sum = (n - 1) << (n - 2);
    for (int S = 0; S < (1 << n); ++S) {

        int mx = 0;
        for (auto &x : states) {
            int cur = 0;
            for (int i = 0; i < n; ++i) {
                if (!(S >> i & 1))
                    continue;
                int p = x.v[i][0], q = x.v[i][1], r = x.v[i][2];
                if (p) cur += S >> (p - 1) & 1;
                if (q) cur += S >> (q - 1) & 1;
                if (r) cur += S >> (r - 1) & 1;
            }
            if (cur > mx)
                mx = cur;
        }
        // printf("%d: %d\n", S, mx);
        sum += mx;
    }
    printf("%.10f\n", sum);
    sum /= 1 << n;

    return 0;
}
