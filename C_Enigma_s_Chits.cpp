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
    ll a , b , c; 
    cin>>a >> b >> c;
    if(b%2!=0){
        cout<<-1<<endl;
        return;
    }
    vector<pair<ll,ll>> vp;
    ll last = 2 * (a + b +c);
    ll cur =0;

    if(c>=3){
        ll x = c/3;
        while(x--){
            for(ll i=cur+1; i<=cur+3;i++){
                vp.push_back({i,i+3});
            }
            cur+=6;
        }
        c = c%3;
    }
    if(c<=2){
        if(c == 2 && b >= 2){
            vp.push_back({cur+1, cur+3}); // diff 2
            vp.push_back({cur+2, cur+5}); // diff 3
            vp.push_back({cur+4, cur+7}); // diff 3
            vp.push_back({cur+6, cur+8}); // diff 2

            cur += 8;
            b-=2;
            c-=2;
        }
        while(c && b){
            vp.push_back({cur+1,cur+3});
            vp.push_back({cur+4,cur+6});
            vp.push_back({cur+2,cur+5});
            cur+=6;
            c-=1;
            b-=2;
        }
        while(c && a){
            vp.push_back({cur+1,cur+4});
            vp.push_back({cur+2,cur+3});
            cur+=4;
            c-=1;
            a-=1;
        }
        if(c){
            cout<<-1<<endl;
            return;
        }
    }
    // c must be zero;

    if(b){
        while(b>=2){
            vp.push_back({cur+1,cur+3});
            vp.push_back({cur+2,cur+4});
            cur+=4;
            b-=2;
        }
        if(b){
            cout<<-1<<endl;
            return;
        }
    }
    if(a){
        while(a){
            vp.push_back({cur+1,cur+2});
            cur+=2;
            a-=1;
        }
    }
    if(a==0 && b==0 && c==0){
        for(auto &p: vp){
            cout<<p.first<<" "<<p.second<<endl;
        }
    }
    else{
        cout<<-1<<endl;
    }

    
}

int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    test
        solve();
    return 0;
}