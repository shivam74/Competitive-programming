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

void dfs(vector<vector<ll>> &v, ll node, ll par,ll dist, map<ll, map<ll, ll>> &m) {
    m[1][node] = dist;
    for (auto &ver : v[node]) {
       if(ver!=par){
        dfs(v,ver,node,dist+1,m);
       }
    }
}

void count_node(vector<vector<ll>> &v,ll node,ll par,vector<ll> &cnt){
    cnt[node]=1;
    for(auto &ver : v[node]){
        if(ver!=par){
            count_node(v,ver,node,cnt);
            cnt[node]+=cnt[ver];
        }
    }
}

void count_ans(vector<vector<ll>> &v, ll n,ll node, ll par, vector<ll> &cnt, vector<ll> &ans) {
    for (auto adj : v[node]) {
        if (adj==par) continue; 
        ll x=n-cnt[adj]-1;
        x-=cnt[adj]-1;
        ans[adj]=ans[node] + x;
        count_ans(v,n, adj, node, cnt, ans);
    }
}

void solve(){
    ll n;
    cin>>n;
    vector<vector<ll>> v(n+1);
    map<ll,map<ll,ll>> m;
    for(ll i=1;i<n;i++){
        ll x,y;
        cin>>x>>y;
        v[x].push_back(y);
        v[y].push_back(x);
    }
    dfs(v,1,0,0,m);
    ll sum=0;
    for(ll i=2;i<=n;i++){
        sum+=m[1][i];
    }
    vll ans(n+1);
    ans[1]=sum;
    vll cnt(n+1);
    count_node(v,1,0,cnt);
    count_ans(v,n,1,0,cnt,ans);
    // for(auto &x: cnt){
    //     cout<<x<<endl;
    // }
    for(ll i=1;i<=n;i++){
        cout<<ans[i]<<" ";
    }
}

int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //test
        solve();
    return 0;
}