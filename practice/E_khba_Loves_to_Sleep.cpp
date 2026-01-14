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

set<ll> check(ll val,ll k,vll v,ll x,ll n){
    set<ll> ans;
    for(ll i=1;i<n;i++){
        ll fi=v[i-1]+val; 
        ll lst=v[i]-val;
        while(ans.size()<k && fi<=lst){
            ans.insert(fi);
            fi++;
        }
    }
    //left
    ll fi=0; 
    ll lst=v[0]-val;
    while(ans.size()<k && fi<=lst){
        ans.insert(fi);
        fi++;
    }
    //right
    fi=v[n-1]+val; lst=x;
    while(ans.size()<k && fi<=lst){
        ans.insert(fi);
        fi++;
    }
    return ans;
}

void solve(){
    ll n,k,x;
    cin>>n>>k>>x;
    vll v(n);
    for(auto &x:v)cin>>x;
    sort(all(v));
    set<ll> ans;
    ll lo=0,hi=1e9;
    sort(all(v));
    while(lo<=hi){
        ll mid=lo+(hi-lo)/2;
        set<ll> temp=check(mid,k,v,x,n);
        if(temp.size()==k){
            ans=temp;
            lo=mid+1;
        }
        else hi=mid-1;
    }
    for(auto &x:ans){
        cout<<x<<" ";
    }
    cout<<endl;
     
}

int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    test
        solve();
    return 0;
}