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

typedef tree<
    long long,
    null_type,
    less<long long>,
    rb_tree_tag,
    tree_order_statistics_node_update
> ordered_set;

struct DSU {
    vll p, sz;
    DSU(ll n = 0) { init(n); }
    void init(ll n) {
        p.resize(n);
        sz.assign(n, 1);
        iota(all(p), 0);
    }
    ll findp(ll x) {
        while (x != p[x]) x = p[x] = p[p[x]];
        return x;
    }
    bool unite(ll a, ll b) {
        a = findp(a); b = findp(b);
        if (a == b) return false;
        if (sz[a] < sz[b]) swap(a, b);
        p[b] = a;
        sz[a] += sz[b];
        return true;
    }
};

 struct Edge {
    ll w, u, v;
};

bool cmpEdge(const Edge &x, const Edge &y) {
    return x.w < y.w;
}

void solve(ll t) {
    ll n; cin >> n;
    vll a(n);
    fl(i,0,n-1) cin >> a[i];
    vector<Edge> edges;
    edges.reserve(2*n);
    fl(i,0,n-1) edges.push_back({a[i], 0, i+1});
    fl(i,1,n-1) edges.push_back({abs(a[i]-a[i-1]), i, i+1});
    
    sort(all(edges), cmpEdge);

    DSU d(n+1);
    ll comps = n+1, ans = 0;

    for(auto &e :edges) {
        if (d.unite(e.u, e.v)) {
            ans = e.w;
            if (--comps == 1) break;
        }
    }
    cout<<"Case #"<<t<< ": "<<ans<<"\n";
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll t;
    cin>>t;
    fl(i,1,t)solve(i);
    return 0;
}