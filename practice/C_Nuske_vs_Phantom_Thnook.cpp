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
ll get(vector<vector<int>>& pref, int x1, int y1, int x2, int y2){
    if(x1 > x2 || y1 > y2) return 0;
    return pref[x2][y2]
         - pref[x1-1][y2]
         - pref[x2][y1-1]
         + pref[x1-1][y1-1];
}

void solve(){
    ll n,m ; cin>>n>>m;
    ll q; cin>>q;
    string s[n];
    for(ll i=0;i<n;i++){
        cin>>s[i];
    }

    //nodes
    vector<vector<int>> nodes(n+1,vector<int>(m+1,0));
    vector<vector<int>> hori(n+1,vector<int>(m+1,0));
    vector<vector<int>> ver(n+1,vector<int>(m+1,0));
    for(ll i=0;i<n;i++){
        for(ll j=0;j<m;j++){
            int val = (s[i][j]=='1');
            nodes[i+1][j+1] = nodes[i][j+1] + nodes[i+1][j] - nodes[i][j] + val;

            int val1 = (j>0 && s[i][j]=='1' && s[i][j-1]=='1');
            hori[i+1][j+1] = hori[i][j+1] + hori[i+1][j] - hori[i][j] + val1;

            int val2 = (i>0 && s[i][j]=='1' && s[i-1][j]=='1');
            ver[i+1][j+1] = ver[i][j+1] + ver[i+1][j] - ver[i][j] + val2;
        }
    }

    while(q--){
        ll x1,y1, x2, y2; 
        cin>>x1>>y1>>x2>>y2;
        cout<<get(nodes,x1,y1,x2,y2)-get(hori,x1,y1+1,x2,y2)-get(ver,x1+1,y1,x2,y2)<<nl;
    }
}

int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //test
        solve();
    return 0;
}