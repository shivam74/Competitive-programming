#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define INF 5*1e18
typedef unsigned long long ull;
typedef long double lld;

#define test ll t; cin >> t; while(t--)
#define vll vector<ll>
#define all(v) v.begin(),v.end()
#define fl(i,f,d) for(ll i=f;i<=d;i++)
#define rl(i,f,d) for(ll i=f;i>=d;i--)
#define nl "\n"
#define setbits(n)  __builtin_popcountll(n)
#define bitsize(n) (63 - __builtin_clzll(n))
#define lcm(a,b) (a/__gcd(a, b)*b)

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

// Ordered Set Template (Ordered multiset)
//ordered_set s;
//s.order_of_key(x) it give no. of elements less than x
//s.find_by_order(i) (i->[0-(n-1)]) it give the iterator of i'th element in the set
typedef tree<
    long long, //pii(pair<ll,ll>
    null_type,
    less<long long>,//less<pii>
    rb_tree_tag,
    tree_order_statistics_node_update
> ordered_set;//ordered_multiset



bool isprime(ll x){
    if (x < 2) return false;
    if (x == 2) return true;
    if (x % 2 == 0) return false;
    for(ll i = 3; i * i <= x; i += 2){
        if (x % i == 0) return false;
    }
    return true;
}

ll mod = 1e9+7;
vector<ll> primeFactors(ll n) {
    vector<ll> factors;
    while (n % 2 == 0) { factors.push_back(2); n /= 2; }
    for(ll i=3; i*i<=n; i+=2){
        while(n % i == 0){ factors.push_back(i); n /= i; }
    }
    if(n != 1) factors.push_back(n);
    return factors;
}

ll modExp(ll a, ll b, ll mod){
     a%=mod;
      ll res=1;              
      while(b){
          if(b & 1){
              res=res*a %mod;
          }
          a=a*a % mod;
          b/=2;
      }
      return res;
}
long long modInverse(long long a, long long mod) {
    return modExp(a, mod - 2, mod);
}
//priority_queue<int, vector<int>, greater<int>> minPQ;

//------------------------Solution starts from here------------------------

void solve(){
    ll n; cin>>n;
    ll x,y,p,q;
    cin>>x>>y>>p>>q;
    vector<pair<ll,ll>> v(n);
    fl(i,0,n-1){
        ll x1; cin>>x1;
        v[i].first=x1;
    }
    fl(i,0,n-1){
        ll y1; cin>>y1;
        v[i].second=y1;
    }
    sort(all(v));
    vector<tuple<ll,ll,ll>> groups;
    groups.push_back({x,y,y});
    groups.push_back({v[0].first,v[0].second,v[0].second});
    for(ll i=1;i<n;i++){
        ll lst=groups.size()-1;
        if(v[i].first==v[i-1].first){
            get<2>(groups[lst])=v[i].second;
        }
        else{
            groups.push_back({v[i].first,v[i].second,v[i].second});
        }
    }
    groups.push_back({p,q,q});

    ll m=groups.size();
    // for(ll i=0 ; i<m ; i++){
    //     for(auto &[a,b,c]:groups){
    //         cout<<a<<' '<<b<<" "<<c<<nl;
    //     }
    // }
    vector<vector<ll>> dp(m+2,vector<ll>(2));
    for(ll i=1;i<m;i++){
        ll highi=get<2>(groups[i]),lowi=get<1>(groups[i]);
        ll highp=get<2>(groups[i-1]),lowp=get<1>(groups[i-1]);

        dp[i][0]=abs(get<0>(groups[i-1])-get<0>(groups[i])) +highi-lowi + min(dp[i-1][0]+abs(highp-lowi) ,dp[i-1][1]+abs(lowp-lowi));
        dp[i][1]=abs(get<0>(groups[i-1])-get<0>(groups[i])) +highi-lowi + min(dp[i-1][0]+abs(highp-highi) ,dp[i-1][1]+abs(lowp-highi));
    }
    cout<<dp[m-1][1]<<nl;
}

int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    test
        solve();
    return 0;
}