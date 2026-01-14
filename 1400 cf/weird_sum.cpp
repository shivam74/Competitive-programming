//https://codeforces.com/contest/1648/problem/A
// Shivam Raghuwanshi's code
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define INF 1e9
typedef unsigned long long ull;
typedef long double lld;

#define test  \
    ll t;     \
    cin >> t; \
    while (t--)
#define vll vector<ll>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

// Ordered Set Template
typedef tree<
    long long,                        // Data type (e.g., int, pair<int, int>)
    null_type,                        // Mapped type (use null_type for a set)
    less<long long>,                  // Comparison function (less for ascending order)
    rb_tree_tag,                      // Underlying data structure (red-black tree)
    tree_order_statistics_node_update // Custom policy for order statistics
    >
    ordered_set;

bool cmp(ll a, ll b)
{
    return a > b;
}
bool cmpbyfirst(pair<ll, ll> a, pair<ll, ll> b)
{
    return a.first < b.first;
}
bool cmpbysec(pair<ll, ll> a, pair<ll, ll> b)
{
    return a.second < b.second;
}

bool isprime(ll x)
{
    if (x < 2)
        return false;
    if (x == 2)
        return true;
    if (x % 2 == 0)
        return false;
    for (ll i = 3; i * i <= x; i += 2)
    {
        if (x % i == 0)
        {
            return false;
        }
    }
    return true;
}
ll mod = 1e9 + 7;
vector<ll> primeFactors(ll n)
{
    vector<ll> factors;
    while (n % 2 == 0)
    {
        factors.push_back(2);
        n /= 2;
    }
    for (ll i = 3; i * i <= n; i += 2)
    {
        while (n % i == 0)
        {
            factors.push_back(i);
            n /= i;
        }
    }
    if (n != 1)
    {
        factors.push_back(n);
    }
    return factors;
}

ll dp[100005];

ll fun(ll x)
{
    return pow(3, x + 1) + x * pow(3, x - 1);
}

void solve()
{
    ll n, m;
    cin >> n >> m;
    vector<vector<pair<ll,ll>>> v(100000+1);
    set<ll> colors;
    ll cur = 0;

    for (ll i = 0; i < n; i++)
    {
        for (ll j = 0; j < m; j++)
        {
            ll x;
            cin>>x;
            v[x].push_back({i,j});
        }
    }
    for (ll i = 1; i <= n; i++)
    {
       
    }
    for (ll i = 1; i <= m; i++)
    {

    }
    ll ans = 0;
    for (ll i = 1; i < n; i++)
    {
     
    }

    cout << ans << endl;
}

int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
     test
    solve();
    return 0;
}