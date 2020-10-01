#include <bits/stdc++.h>
using namespace std;

long long MOD = 1000000007;

int main() 
{
    long long increase = 0, decrease = 0;    

    vector<vector<long long>> inc(100010, vector<long long>(20, 0)), dec = inc;
    vector<long long> ans(100010, 0);
    int n = 100000;
    
    for(int i=1; i<n; i++)
    {
        for(int j=0; j<=9; j++)
        {
            for(int k=0; k<=9; k++)
            {
                if(k >= j) 
                {
                    if(i == n-1 || j > 0) 
                    {
                        inc[i][j] = (inc[i][j] + inc[i-1][k] + (10 - k)) % MOD;
                    }
                }
                if(k <= j)
                {
                    dec[i][j] = (dec[i][j] + dec[i-1][k] + (k + 1)) % MOD;
                }
            }
        }
        increase = inc[i][1] + 9;
        decrease = dec[i][9] - (10 * dec[i][0]);
        ans[i + 1] = (increase + decrease) % MOD;
    }    
    
    int t;
    cin >> t;
    
    while(t--)
    {
        cin >> n;
        cout << ans[n] << endl;
    }      
    return 0;
}
