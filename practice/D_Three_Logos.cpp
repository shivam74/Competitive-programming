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


pair<int,int> fillRect(vector<vector<ll>> &rect,ll x,ll y,ll type){
    ll n = rect.size()-1;
    bool ok=0;
    ll xx,yy;
    for(ll i=1;i<=n;i++){
        for(ll j=1;j<=n;j++){
            if(rect[i][j]==0){
                if(n-i+1>=x && n-j+1>=y){
                    ok=1;
                    xx = i; 
                    yy =j;
                    break;
                }
            }
        }
        if(ok)break;
    }
    if(!ok) return {0,0};
    for(ll i=xx; i<=xx+x-1 ;i++){
        for(ll j=yy  ; j<=yy+y-1 ; j++){
            rect[i][j]=type+1;
        }
    }
    return {xx,yy};
}

void unfill(vector<vector<ll>> &rect,ll x,ll y, ll xx,ll yy){
    for(ll i=xx; i<=xx+x-1 ;i++){
        for(ll j=yy  ; j<=yy+y-1 ; j++){
            rect[i][j]=0;
        }
    }
}

bool searchComb(vector<vector<ll>> &rect,ll cur,vll &perm,vector<pair<int,int>> &sizes){
    ll n= rect.size()-1;
    if(cur==3){
        bool ok = 1; 
        for(ll i=1;i<=n; i++){
            for(ll j=1;j<=n;j++){
                if(rect[i][j]==0){
                    ok=0;
                    break;
                }
            }
            if(!ok)break;
        }
        return ok;
    }
    ll x = sizes[perm[cur]].first, y = sizes[perm[cur]].second;
    pair<int,int> p= fillRect(rect,x,y,perm[cur]);
    if(p.first !=0){
        bool ok=searchComb(rect,cur+1,perm,sizes);
        if(ok){
            return ok;
        }
        unfill(rect,x,y,p.first,p.second);
    }
    p=fillRect(rect,y,x,perm[cur]);
    if(p.first !=0){
        bool ok=searchComb(rect,cur+1,perm,sizes);
        if(ok){
            return ok;
        }
        unfill(rect,y,x,p.first,p.second);
    }
    return 0;
}



void solve(){
    ll x1,x2,x3,y1,y2,y3;
    cin>>x1>>y1>>x2>>y2>>x3>>y3;
    ll sum = x1*y1 + x2*y2 + x3*y3;
    ll sq = sqrt(sum);
    if(sq*sq!=sum){
        cout<<-1<<nl;
        return;
    }
    vector<pair<int,int>> sizes = {{x1,y1},{x2,y2},{x3,y3}};
    vector<vector<ll>> rect(sq+1,vector<ll>(sq+1));
    vll perm(3);
    iota(perm.begin(),perm.end(),0);
     bool ok=0;
    do{
       ok =searchComb(rect,0,perm,sizes);
        if(ok) break;
    }
    while(next_permutation(perm.begin(),perm.end()));
    if(!ok){
        cout<<-1<<nl;
        return;
    }
    cout<<sq<<nl;
    for(ll i=1;i<=sq;i++){
        for(ll j=1;j<=sq; j++){
            if(rect[i][j]==1)cout<<'A';
            if(rect[i][j]==2)cout<<'B';
            if(rect[i][j]==3)cout<<'C';
        }
        cout<<nl;
    }

}

int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //test
        solve();
    return 0;
}