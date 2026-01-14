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

const ll MAXN= 7*1e5+5;

vector<int> g[MAXN];
bool vis[MAXN];
int parent[MAXN];

bool bfs(ll s,ll t,vll &ans){
    for(ll i=0;i<MAXN;i++){
        parent[i]=-1;
        vis[i]=0;
    }
    queue<ll> q;
    q.push(s);
    vis[s]=true;
    while(!q.empty()){
        ll p= q.front();
        q.pop();
        if(p==t){
            break;
        }
        for(auto &v:g[p]){
            if(vis[v])continue;
            vis[v]=true;
            parent[v]=p;
            q.push(v);
        }
    }
    if(vis[t]==false)return false;
    for(ll i=t;i!=-1;i=parent[i]){
        ans.push_back(i);
    }
    reverse(all(ans));
    return true;
}
void solve(){
    ll n;
    cin>>n;
    ll offs=3*1e5+5;
    vll v(n+1);
    fl(i,1,n)cin>>v[i];
    ll s,t;
    cin>>s>>t;
    set<ll> pf;
    //vector<vector<ll>> g(3*offs+5);
    for(ll i=1;i<=n;i++){
        vll p=primeFactors(v[i]);
        for(auto &x:p){
            g[i].push_back(x+offs);
            g[x+offs].push_back(i);
        }
    }
    vll ans;
    if(bfs(s,t,ans)){
        vll final;
        for(auto &x:ans){
            if(x<offs)final.push_back(x);
        }
        cout<<final.size()<<endl;
        for(auto &x:final){
            cout<<x<<" ";
        }
        cout<<endl;
    }
    else{
        cout<<-1<<endl;
    }
    

}

int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
   // test
        solve();
    return 0;
}