#include "fmt/format.h"
using namespace fmt;

namespace PE610 {
    char SS[] = "IVXLCDM#", stack[100];
    int top = 0;

    struct node {
        node *c[8];
        double value;

        node() : value(-1) {
            for (int i = 0; i < 8; ++i) {
                c[i] = nullptr;
            }
        }

        node *go(int x) {
            if (c[x] == nullptr) {
                c[x] = new node();
            }
            return c[x];
        }
    };

    node *root;

    node *go(node *t, int X, int V, int I, int m) {
        if (m == 9) {
            t = t->go(I);
            t = t->go(X);
        } else if (5 <= m && m <= 8) {
            t = t->go(V);
            for (int i = 1; i <= m - 5; ++i) {
                t = t->go(I);
            }
        } else if (m == 4) {
            t = t->go(I);
            t = t->go(V);
        } else {
            for (int i = 1; i <= m; ++i) {
                t = t->go(I);
            }
        }
        return t;
    }

    void generate(int n) {
        node *t = root;
        t = go(t, 6, 5, 4, n / 100 % 10);
        t = go(t, 4, 3, 2, n / 10  % 10);
        t = go(t, 2, 1, 0, n / 1   % 10);
        t = t->go(7);
        t->value = n;
    }

    double compute(node *t) {
        if (t->value >= 0) {
            stack[top] = '\0';
            print("{} {}\n", stack, t->value);
            return t->value;
        }
        double sum = 0, cnt = 0;
        for (int i = 0; i < 8; ++i) {
            if (t->c[i] != nullptr) {
                double w = i == 7 ? 0.02 : 0.14;
                cnt += w;
                stack[top] = SS[i]; ++top;
                sum += compute(t->c[i]) * w;
                --top;
            }
        }
        // if (cnt == 100)
        // print("{} {}\n", sum, cnt);
        return t->value = sum / cnt;
    }

    void main() {
        root = new node();
        for (int i = 0; i < 1000; ++i) {
            generate(i);
        }
        double ans = 140 / 0.86 + compute(root);
        print("ans = {:.9f}, root = {:.8f}\n", ans, root->value);
    }
}

int main() {
    PE610::main();
    return 0;
}
