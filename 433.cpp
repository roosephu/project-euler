#include <iostream>
#include <ctime>
#include <cstring>
using namespace std;

const int N = 5000030;

int n = 200000;

typedef long long int64;

int64 ans = 0;
int cnt[N];

// void dfs(int a, int b, int d)
// {
//     cnt[b] += d; ++d;
//     for ( ; (a += b) <= n; )
//         dfs(b, a, d);
// }

int Q[N];

void dfs(int a, int b, int d)
{
    int t = 1, *p = Q + 1; Q[0] = 1, Q[1] = 1;
    for (; ; ) {
        for (; p != Q && (*p += *(p - 1)) > n; --p);
        if (p == Q) break;
        // for (int i = 0; i <= t; ++i) {
        //     cerr << Q[i] << " ";
        // }
        // cerr << endl;
        cnt[*p] += p - Q;
        *(p + 1) = *(p - 1), ++p;
    }
}

int main()
{
    int64 lx = 0;
    for (; ; ++n) {
        ans = 0;
        memset(cnt, 0, sizeof(cnt));
        // for (int i = 2; i <= n; ++i)
        //     dfs(1, i, 1);
        dfs(1, 1, 1);
    
        // cout << "--------------------" << endl;
        int sum = 0;
        // cout << n << endl;
        for (int i = 2; i <= n; ++i) {
            ans += n / i * cnt[i];
            // cout << cnt[i] << " ";
            sum += cnt[i];
        }
        // cout << endl;
        // cout << sum << endl;
        ans = ans * 2 + n + n * (n - 1ll) / 2;
        cout << n << " " << ans << " " << (ans - lx + n) / 2 << endl;
        lx = ans;
        break;
    }
    cout << 1.0 * clock() / CLOCKS_PER_SEC << endl;
    return 0;
}
