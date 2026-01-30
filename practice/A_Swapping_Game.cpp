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

//------------------------Solution starts from here------------------------

ll cntInversion(vector<ll> &p,vector<ll> &q,ll l){
    vector<ll> pos(l+1);
    for(ll i=0;i<l;i++){
        pos[p[i]]=i;
    }
    ll cnt=0;
    

    for(ll i=0;i<l;i++){
        for(ll j=i+1;j<l;j++){
            if(pos[q[i]]>pos[q[j]]){
                cnt++;
            }
        }
    }
    return cnt;
}

void solve(){
    ll n,l; cin>>n>>l;
    vector<ll> dp(n+1);
    vector<ll> mxDp(n+1);
    vector<vector<ll>> v(n+1);
    vector<ll> vi;
    for(ll i=1;i<=l;i++){
        vi.push_back(i);
    }
    
    for(ll i=1;i<=n;i++){
        ll c; cin>>c;
        for(ll j=0;j<l;j++){
            ll x; cin>>x;
            v[i].push_back(x);
        }      
        ll cnt=cntInversion(vi,v[i],l);
        if(cnt<=i)dp[i]=c;
        ll mx=0;
        ll m=(l*(l-1))/2;
        for(ll j=1;j<=m && i-j>0;j++){
            ll cnti=cntInversion(v[i-j],v[i],l);
            if(cnti<=j)mx=max(mx,dp[i-j]);
        }
        mx=max(mxDp[max(0ll,i-m-1)],mx);
        dp[i]+=mx;
        mxDp[i]=max(mxDp[i-1],dp[i]);
    }
    ll ans=0;
    for(ll i=1;i<=n;i++){
        ans=max(ans,dp[i]);
    }
    cout<<ans<<endl;
}

int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //test
        solve();
    return 0;
}