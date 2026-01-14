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
    ll n;
    cin>>n;
    ll x,y; cin>>x>>y;
    if(n==12){
        if(x==y)cout<<"2A0B"<<endl;
        else cout<<"0A2B"<<endl;
        return;
    }
    if(n==123){
        vll v={0,123,132,213,231,312,321};
        if(x==y){
            cout<<"3A0B"<<endl;
            return;
        }
        x=v[x],y=v[y];
        ll cnt=0;
        while(x){
            ll p=x%10;
            ll q=y%10;
            if(p==q)cnt++;
            x/=10; y/=10;
        }
        cout<<cnt<<"A"<<3-cnt<<"B"<<endl;
        return;
    }
    if(n==1234){
        vll v={0,1234,1243,1324,1342,1423,1432,2134,2143,2314,2341,2413,2431,3124,3142,3214,3241,3412,3421,4123,4132,4213,4231,4312,4321};
        if(x==y){cout<<"4A0B"<<endl; return;}
        x=v[x],y=v[y];
        ll cnt=0;
        while(x){
            ll p=x%10;
            ll q=y%10;
            if(p==q)cnt++;
            x/=10; y/=10;
        }
        cout<<cnt<<"A"<<4-cnt<<"B"<<endl;
        return;
    }
}

int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    test
        solve();
    return 0;
}