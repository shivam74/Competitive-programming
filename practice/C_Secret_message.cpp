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

set<char> fun(set<char> &common,set<char> &initial){
    set<char> res=common;
    for(auto &x : common){
        if(initial.find(x)==initial.end()){
            res.erase(res.find(x));
        }
    }
    return res;
}

void solve(){
    ll l; cin>>l;
    ll n; cin>>n;
    string s[n];
    fl(i,0,n-1){
        cin>>s[i];
    }
    set<char> st[l];
    fl(i,0,n-1){
        for(ll j=0;j<l;j++){
            st[j].insert(s[i][j]);
        }
    }
    set<ll> divisors;
    
    for(ll i=1;i*i<=l;i++){
        if(l%i==0){
            divisors.insert(i);
            if(i!=l/i)divisors.insert(l/i);
        }
    }
    string ans;
    ll cnt=0;
    for(auto len: divisors){
        set<char> common[len];
        ll flag=1;
        for(ll i=0;i<len;i++){
            common[i]=st[i];
        }
        for(ll cur=len;cur<l;cur+=len){
            for(ll j=cur;j-cur<len;j++){
                common[j-cur]=fun(common[j-cur],st[j]);
                if(common[j-cur].empty()){
                    flag=0;
                    break;
                }
            }
            if(flag==0){
                break;
            }
        }    
        if(flag){
            for(auto &x : common){
                auto it = x.begin() ;
                ans+=*(it);
                cnt++;
            }
            break;
        }

    }

    cnt=l/cnt;
    //cout<<cnt<<nl;
    string final;
    while(cnt--){
        final+=ans;
    }
    cout<<final<<nl;
}

int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    test
        solve();
    return 0;
}