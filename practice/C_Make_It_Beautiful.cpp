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

void solve(){
    ll n,k; cin>>n>>k;
    vll v(n); fl(i,0,n-1)cin>>v[i];
    ll ans=0;
    ll cnt=0;
    vll cnt_bit(64);
    for(ll i=0;i<n;i++){
        //cout<<__builtin_popcountll(v[i])<<nl;
        if(v[i]%2==0 && k>0){
            v[i]+=1;
            k--;
        }
        for(ll j=0;j<64;j++){
            if(((v[i]>>j) & 1ll)==0){
                cnt_bit[j]++;
            }
        }
        ans+= __builtin_popcountll(v[i]);
    }
    // for(ll j=0;j<64;j++){
    //         cout<<cnt_bit[j]<<" ";
    //     }
    //     cout<<endl;
    if(k>0){
        for(ll i=0;i<64;i++){
            ll x=pow(2,i);
            ll y=min(k/x,cnt_bit[i]);
            ans+=y;
            k-=y*x;
        }
    }
    cout<<ans<<nl;
}

int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    test
        solve();
    return 0;
}