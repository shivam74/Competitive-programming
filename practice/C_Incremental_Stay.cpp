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

void solve(){
    ll n;
    cin>>n;
    vll v(2*n+1);
    fl(i,1,2*n)cin>>v[i];
    vll prefix(n+1),suffix(n+1);
    fl(i,1,n){
        prefix[i]=prefix[i-1]+(v[i+1]-v[i])*i;
    }
    rl(i,n-1,1){
        suffix[n-i]=suffix[n-i-1]+(v[n+i+1]-v[n+i])*(n-i);
    }
    // fl(i,1,n){
    //     cout<<prefix[i]<<" ";
    // }
    // cout<<endl;
    // fl(i,1,n){
    //     cout<<suffix[i]<<" ";
    // }
    //cout<<endl;
    vll ans(n+1);
    vll pre_odd(n+1),pre_even(n+1);
    ll l=n,r=n+1;
    rl(i,n-1,1){
        if(l%2==0){
            pre_even[i]=pre_even[i+1]+abs(v[l]-v[l+1]);
            pre_odd[i]=pre_odd[i+1]+abs(v[r]-v[r+1]);
        }
        else{
            pre_even[i]=pre_even[i+1]+abs(v[r]-v[r+1]);
            pre_odd[i]=pre_odd[i+1]+abs(v[l]-v[l+1]);
        }
        l--; r++;
    }
    // fl(i,1,n){
    //     cout<<pre_odd[i]<<" ";
    // }
    // cout<<endl;
    // fl(i,1,n){
    //     cout<<pre_even[i]<<" ";
    // }
    // cout<<endl;
    fl(i,1,n){
        if(i%2==0){
            ans[i]+=prefix[i];
             ans[i]+=suffix[i-1];
             ans[i]+=(pre_odd[i]*(i-1))+pre_even[i]*i;
        }
        else{
            ans[i]+=prefix[i];
            ans[i]+=suffix[i-1];
            ans[i]+=(pre_even[i]*(i-1))+pre_odd[i]*i;
        }
    }
    fl(i,1,n){
        cout<<ans[i]<<" ";
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