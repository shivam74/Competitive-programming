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
    ll n; cin>>n;
    vll v(n+1);
    fl(i,1,n)cin>>v[i];
    ll a1,a2,b1,b2,c1,c2;
    a1=1,a2=2,b1=n-1+1,b2=n-2+1,c1=v[1],c2=v[2];
    ll det=a1*b2-a2*b1,detx=c1*b2-b1*c2,dety=a1*c2-a2*c1;
    ll x=-1,y=-1;
    if(det!=0 && detx%det==0 ){
        x=detx/det;
    }
    if(det!=0 && dety%det==0 ){
        y=dety/det;
    }
    //cout<<x<<" "<<y<<nl;
    if(x<0 || y<0){
        cout<<"NO"<<nl;
        return;
    }
    for(ll i=3;i<=n;i++){
        a1=i-1,a2=i,b1=n-i+1+1,b2=n-i+1,c1=v[i-1],c2=v[i];
        det=a1*b2-a2*b1,detx=c1*b2-b1*c2,dety=a1*c2-a2*c1;
        ll x1=-1,y1=-1;
        if(det!=0 && detx%det==0){
            x1=detx/det;
        }
        if(det!=0 && dety%det==0 ){
            y1=dety/det;
        }
        if(x1!=x || y1!=y){
            cout<<"NO"<<nl;
            return;
        } 
    }
    cout<<"YES"<<nl;
}

int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    test
        solve();
    return 0;
}