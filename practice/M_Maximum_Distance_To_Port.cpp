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


//some reminders....
//if stuck change the perpective of finding answers
//for maximizing/minizing think on bs on answers
//in bits manupulation check long long errors

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
//------------------------Solutions starts from here------------------------

void bfs(vector<vector<ll>> &graph,vector<ll> &dis,ll n){
   // fill(dis.begin(),dis.end(),-1);
    vll vis(n+1);
    queue<ll> q;
    q.push(1);
    vis[1]=1;
    while(!q.empty()){
        ll cur=q.front();
        q.pop();
        for(auto &adj : graph[cur]){
            if(!vis[adj]){
                dis[adj]=1+dis[cur];
                q.push(adj);
                vis[adj]=1;
            }
        }
    }  
}

void solve(){
    ll n,e,k; cin>>n>>e>>k;
    vll product(n+1); fl(i,1,n)cin>>product[i];
    vector<vector<ll>> graph(n+1);
    fl(i,1,e){
        ll x,y;
        cin>>x>>y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }
    vll dis(n+1);
    bfs(graph,dis,n);
    // for(auto & x: dis){
    //     cout<<x<<" ";
    // }
    //cout<<endl;
    map<ll,ll> mp;
    for(ll i=1;i<=n;i++){
        mp[product[i]]=max(dis[i],mp[product[i]]);
    }
    for(auto &x:mp){
        cout<<x.second<<" ";
    }
}

int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //test
        solve();
    return 0;
}