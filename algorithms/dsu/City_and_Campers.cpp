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

const ll N = 1e5+7;
ll parent[N];
ll sz[N];

void make(ll v){
    parent[v]=v;
    sz[v]=1;
}

ll find(ll v){
    if(parent[v]==v)return v;
    //path compression
    return parent[v]=find(parent[v]);
}

void Union(ll a,ll b){
    a=find(a);
    b=find(b);
    if(a!=b){
        // union by size
        if(sz[a]<sz[b])
            swap(a,b);
        parent[b]=a;
        sz[a]+=sz[b];       
    }
}

void solve(){
    ll n,q;
    cin>>n>>q;
    multiset<ll> st;
    fl(i,1,n){
        make(i);
        st.insert(1);
    }
    while(q--){
        ll a,b;
        cin>>a>>b;
        a=find(a),b=find(b);
        if(a!=b){
            auto it1=st.find(sz[a]);
            st.erase(it1);
            auto it2=st.find(sz[b]);
            st.erase(it2);
            st.insert(sz[a]+sz[b]);
            Union(a,b); 
        }
        if(st.size()==1)cout<<0<<endl;
        else cout<<*st.rbegin()-*st.begin()<<endl;
    }
}

int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //test
        solve();
    return 0;
}