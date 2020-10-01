#include <bits/stdc++.h>
using namespace std;

vector<int> primes;

char *sieve;
int limit;

void Sieve(int n)
{
    limit = (n / 2) + 1;

    sieve = new char[limit];
    fill(sieve, sieve + limit, 1);
    sieve[0] = 0;

    for(int i=1; 2*i*i < limit; i++)
    {
        if(sieve[i])
        {
            for(int j = (3 * i) + 1; j < limit; j += (2 * i) + 1)
            {
                sieve[j] = 0;
            }
        }
    }
}

bool IsPrime(int n)
{
    if(n < 2) return 0;
    if(n == 2 || n == 3) return 1;
    if(n % 2 == 0 || n % 3 == 0) return 0;

    return sieve[n / 2];
}


int main()
{
    int MAX = 100000000;

    Sieve(MAX);

    for(int i=2; i <= MAX; i++)
    {
        if(IsPrime(i))
        {
            primes.push_back(i);
        }
    }
    int t;
    cin >> t;

    while(t--)
    {
        int n;
        cin >> n;

        int ans = 0;

        for(int i=0; i < primes.size(); i++)
        {
            if(primes[i] * primes[i] >= n) break;

            for(int j=i; j < primes.size(); j++)
            {
                if(primes[i] * primes[j] >= n) break;

                ans++;
            }
        }
        cout << ans << "\n";
    }
    return 0;
}
