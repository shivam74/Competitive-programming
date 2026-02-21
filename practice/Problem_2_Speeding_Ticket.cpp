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


vector<bool> seive_of_eratosthenes(ll n){
     vector<bool> v(n+1,1);
     if (n >= 0) v[0] = false;
     if (n >= 1) v[1] = false;
   
     for (ll i = 2; i * i <= n; i++) {
         if (v[i]) { 
             for (ll j = i * i; j <= n; j += i) {
                 v[j] = false;
             }
         }
     }
     return v;
}


//priority_queue<int, vector<int>, greater<int>> minPQ;

//------------------------Solution starts from here------------------------

void solve(){
    ll n; cin>>n;
    ll m; cin>>m;
    vector<pair<ll,ll>> road(n);
    vector<pair<ll,ll>> cow(m);
    for(ll i=0;i<n;i++){
        ll x,y; cin>>x>>y;
        road[i]={x,y};
    }
    for(ll i=0;i<m;i++){
        ll x,y; cin>>x>>y;
        cow[i]={x,y};
    }
    //cout<<1<<nl;
    vll maxSpeed(101);
    ll cur=1;
    //cout<<cur<<nl;
    for(ll i=0;i<n;i++){
        ll mx=cur+road[i].first;
        for(cur;cur<mx;cur++){
            maxSpeed[cur]=road[i].second;
        }
    }
    cur=1;
    vll curSpeed(101);
    for(ll i=0;i<m;i++){
        ll mx=cur+cow[i].first;
        for(cur;cur<mx;cur++){
            curSpeed[cur]=cow[i].second;
        }
    }
    ll ans=0;
    for(ll i=1;i<=100;i++){
       // cout<<maxSpeed[i]<<" "<<curSpeed[i]<<nl;
        ans=max(ans,(curSpeed[i]-maxSpeed[i]));
    }
    //cout<<nl;
    cout<<ans<<nl;
    
}

int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string problem = "speeding";
    freopen((problem + ".in").c_str(), "r", stdin);
    freopen((problem + ".out").c_str(), "w", stdout);
    //test
        solve();
    return 0;
}