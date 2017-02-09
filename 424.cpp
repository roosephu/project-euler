#include "fmt/format.h"
#include <cstring>
#include <vector>
using namespace fmt;
using namespace std;

const int N = 8;

struct Equation {
    vector<int> left;
    int right;
    int dec;
    int vars;
};

vector<Equation> equs;
char G[N][N][10];
int vars[N][N];
int n, num_vars;
int values[N * N], alls;
int ctz[1 << 10], popcnt[1 << 10];

char *parse(int i, int j, char *p) {
    char type = *p;
    Equation equ;
    if (p[2] == ',' || p[2] == ')') {
        equ.dec = -1;
        equ.right = p[1] - 'A';
    } else {
        equ.dec = p[1] - 'A';
        equ.right = p[2] - 'A';
        // state[equ.dec] &= 0xf;
    }

    if (type == 'h') {
        for (int x = j + 1; x < n && vars[i][x] >= 0; ++x)
            equ.left.push_back(vars[i][x]);
    } else if (type == 'v') {
        for (int y = i + 1; y < n && vars[y][j] >= 0; ++y)
            equ.left.push_back(vars[y][j]);
    } else
        assert(0);
    equ.vars = equ.left.size();
    print("dec = {}, right = {}, vars = {}: ", equ.dec, equ.right, equ.vars);
    for (auto v : equ.left)
        print("{} ", v);
    print("\n");

    equs.push_back(equ);
    while (*p != ')' && *p != ',')
        ++p;
    return p;
}

int find_best_var() {
    int mx = 100;
    Equation *e = nullptr;
    for (auto &equ : equs) {
        int undefined = 0;
        if (equ.dec != -1 && values[equ.dec] < 0)
            ++undefined;
        if (values[equ.right] < 0)
            ++undefined;

        for (auto &v : equ.left)
            undefined += values[v] < 0;

        if (undefined < mx && undefined > 0) {
            mx = undefined;
            e = &equ;
        }
    }
    if (!e) {
        for (int i = 0; i < num_vars; ++i) {
            if (values[i] < 0) {
                return i;
            }
        }
    }

    int v[10] = {0};
    if (e->dec != -1 && values[e->dec] < 0)
        v[++v[0]] = e->dec;
    if (values[e->right] < 0)
        v[++v[0]] = e->right;

    for (auto &x : e->left)
        if (values[x] < 0)
            v[++v[0]] = x;
    return v[rand() % v[0] + 1];
}

// int target[] = {8, 4, 2, 6, 0, 3, 9, 5, 7, 1, 1, 9, 6, 8, 7, 1, 9, 3, 2, 1, 4, 3, 7};

bool dfs(int depth) {
    for (auto &equ : equs) {
        int S = 0;
        bool finished = true, found = true;
        int left = 0, right = 0;
        for (auto v : equ.left)
            if (values[v] < 0)
                finished = false, found = false;
            else
                left += values[v], S |= 1 << values[v];

        if (equ.dec >= 0) {
            if (values[equ.dec] < 0) {
                finished = false;
            } else if (values[equ.dec] == 0 || values[equ.dec] >= 4) {
                return false;
            } else {
                right += values[equ.dec] * 10;
            }
        }
        if (values[equ.right] < 0)
            finished = false;
        else
            right += values[equ.right];

        if ((S & 1) || (found && popcnt[S] != equ.vars) || (finished && left != right))
            return false;
    }
    if (depth == num_vars)
        return true;

    int x = find_best_var(), s = x <= 9 ? alls : ((1 << 10) - 2);

    for (; s; ) {
        int v = ctz[s]; s ^= 1 << v;
        values[x] = v;

        // int old = alls;
        if (x <= 9)
            alls ^= 1 << v;
        if (dfs(depth + 1))
            return true;
        if (x <= 9)
            alls ^= 1 << v;
        // assert(old == alls);
        values[x] = -1;
    }
    return false;
}

int main() {
    freopen("p424_kakuro200.txt", "r", stdin);

    for (int i = 1; i < (1 << 10); ++i) {
        popcnt[i] = popcnt[i >> 1] + (i & 1);
        ctz[i] = i & 1 ? 0 : (ctz[i >> 1] + 1);
    }

    long ans = 0; int idx = 0;
    for (char cmd[200]; ~scanf("%s", cmd); ) {
        char *p = cmd;
        ++p, *p = '\0', ++p;

        n = atoi(cmd);
        memset(G, 0, sizeof(G));
        for (int idx = 0, pos = 0, depth = 0; *p; ++p) {
            if (depth == 0 && *p == ',') {
                ++idx;
                pos = 0;
            } else {
                G[idx / n][idx % n][pos++] = *p;
                if (*p == '(') {
                    ++depth;
                } else if (*p == ')') {
                    --depth;
                }
            }
        }

        num_vars = 10;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (strcmp(G[i][j], "O") == 0) {
                    vars[i][j] = num_vars++;
                } else if ('A' <= G[i][j][0] && G[i][j][0] <= 'J') {
                    vars[i][j] = G[i][j][0] - 'A';
                } else {
                    vars[i][j] = -1;
                }
                print("{:10} ", G[i][j]);
            }
            print("\n");
        }
        for (int i = 0; i < num_vars; ++i)
            values[i] = -1;
        alls = (1 << 10) - 1;

        equs.clear();
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (G[i][j][0] == '(') {
                    // print("{} {}: {}\n", i, j, G[i][j]);
                    char *p = G[i][j] + 1;
                    while (*p) {
                        p = parse(i, j, p) + 1;
                    }
                }
            }
        }

        bool found = dfs(0);
        long value = 0;

        if (!found) {
            print("xx\n");
            break;
        } else {
            for (int i = 0; i < n; ++i)  {
                for (int j = 0; j < n; ++j) {
                    if (strcmp(G[i][j], "O") == 0) {
                        G[i][j][0] = '0' + values[vars[i][j]];
                        print("{:10} ", G[i][j]);
                    } else {
                        for (char *p = G[i][j]; *p; ++p) {
                            if ('A' <= *p && *p <= 'J') {
                                *p = '0' + values[*p - 'A'];
                            }
                        }
                        print("{:10} ", G[i][j]);
                    }
                }
                print("\n");
            }
            for (int i = 0; i < 10; ++i) {
                print("{}", values[i]);
                value = value * 10 + values[i];
            }
            print("\n");
        }

        ++idx;
        ans += value;
        print("#{}, solution = {}, ans = {}\n", idx, value, ans);
    }

    return 0;
}
