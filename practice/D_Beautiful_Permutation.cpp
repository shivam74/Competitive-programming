#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define INF 1e9
typedef unsigned long long ull;
typedef long double lld;

#define test ll t; cin >> t; while(t--)
#define vll vector<ll>
#define all(v) v.begin(),v.end()
#define fl(i,f,d) for(ll i=f;i<=d;i++)
#define rl(i,f,d) for(ll i=f;i>=d;i--)

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

// Ordered Set Template
typedef tree<
    long long,
    null_type,
    less<long long>,
    rb_tree_tag,
    tree_order_statistics_node_update
> ordered_set;

vector<vector<ll>> ranks;
bool cmpN(vector<ll> a, vector<ll> b) {
    if(a[0]<b[0]) return true;
    if(b[0]<a[0]) return false;
    else {
        if(ranks[a[2]+1][a[1]] <= ranks[b[2]+1][b[1]]) return true;
        else return false;
    }
}

bool cmpbyfirst(pair<ll,ll> a,pair<ll,ll> b) { return a.first < b.first; }
bool cmpbysec(pair<ll,ll> a,pair<ll,ll> b) { return a.second < b.second; }

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

bool query(ll l,ll r){
    if(l>r)return false;
    ll sum=0;
    //type 1
    cout<<"1 "<<l<<" "<<r<<endl;
    cin>>sum;
    //type 2
    cout<<"2 "<<l<<" "<<r<<endl;
    ll sum1=0;
    cin>>sum1;
    if(sum1==sum)return false;
    else return true;
}

void fun(ll l,ll r, ll &L){
    if(l>r)return;
    ll mid=(l+r)/2;
    if(query(mid,mid)){
        L=min(L,mid);
        fun(l,mid-1,L);
    }
    else{
        if(mid<r)fun(mid+1,r,L);
    }
}

void solve(){
    ll n;
    cin>>n;
    ll l=1,r=n;
    ll L=n+1;
    fun(l,r,L);
    ll len=0;
    cout<<"1 "<<1<<" "<<n<<endl;
    ll y;
    cin>>y;
    cout<<"2 "<<1<<" "<<n<<endl;
    ll x;
    cin>>x;
    len=x-y;
    cout<<"! "<<L<<" "<<L+len-1<<endl;
}

int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    test
        solve();
    return 0;
}