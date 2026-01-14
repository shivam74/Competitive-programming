//https://atcoder.jp/contests/dp/tasks/dp_l
//Shivam Raghuwanshi's code
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define INF 1e9
typedef unsigned long long ull;
typedef long double lld;

#define test ll t; cin >> t; while(t--)
#define vll vector<ll> 

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

// Ordered Set Template
typedef tree<
    long long,                      // Data type (e.g., int, pair<int, int>)
    null_type,                // Mapped type (use null_type for a set)
    less<long long>,                // Comparison function (less for ascending order)
    rb_tree_tag,              // Underlying data structure (red-black tree)
    tree_order_statistics_node_update // Custom policy for order statistics
> ordered_set;

bool cmp(ll a, ll b) {
    return a > b;
}
bool cmpbyfirst(pair<ll,ll> a,pair<ll,ll> b) {
    return a.first < b.first;
}
bool cmpbysec(pair<ll,ll> a,pair<ll,ll> b) {
    return a.second < b.second;
}

bool isprime(ll x){
    if (x < 2) return false;
    if (x == 2) return true;
    if (x % 2 == 0) return false;
    for(ll i = 3; i * i <= x; i += 2){
        if (x % i == 0) {
            return false;
        }
    }
    return true;
}
ll mod = 1e9 +7;
vector<ll> primeFactors(ll n) {
    vector<ll> factors;
    while (n % 2 == 0) {
        factors.push_back(2);
        n /= 2;
    }
    for (ll i = 3; i * i <= n; i += 2) {
        while (n % i == 0) {
            factors.push_back(i);
            n /= i;
        }
    }
    if (n != 1) {
        factors.push_back(n);
    }
    return factors;
}
// X+Y=C
// Y=C-X;
// X-Y= 2X-C
//To maximize X-Y we have to maximize only X as X-Y only depends on X
// similarly to minimize X-Y minimize only X

// we form a dp[i][j][p] which gives the score of player 1 if we consider array from i to j
// dp[i][j][0]=max(v[i]+dp[i+1][j][1],v[j]+dp[i][j-1][1])
// dp[i][j][1]=min(dp[i+1][j][0],dp[i][j-1][0]);
ll dp[3002][3002][2] ;
void solve()
{
    ll n, c = 0;
    cin >> n;
    vector<ll> v(n + 1);
    for (ll i = 1; i <= n; i++)
    {
        cin >> v[i];
        c += v[i];
    }
   
    for (ll i = 1; i <= n; i++)
    {
        dp[i][i][0] = v[i];
        dp[i][i][1] = 0;
    }
    for (ll Rminusl = 1; Rminusl <= n; Rminusl++)
    {
        for (ll l = 1; l + Rminusl <= n; l++)
        {
            ll R = l + Rminusl;
            dp[l][R][0] = max(v[l] + dp[l + 1][R][1], v[R] + dp[l][R - 1][1]);
            dp[l][R][1] = min(dp[l + 1][R][0], dp[l][R - 1][0]);
        }
    }
    cout << 1ll*(2 * dp[1][n][0]) - c;
}


int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //test
        solve();   
    return 0;
}