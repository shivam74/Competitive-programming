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
    ll n,w;
    cin>>n>>w;
    vll v((1<<n)+1);
    vll vis((1<<n)+1);
    ll m=v.size()-1;
    fl(i,1,w-1){
        v[i]=i;
    }
    if(w%2==0){
        v[w]=m;
    }
    ll x=(w%2==0)?w+1:w;
    fl(i,x,m){
        if(w%2==0)v[i]=i-1;
        else v[i]=i;
    }
    reverse(v.begin()+x,v.end());
    auto it=v.begin();
    it++;
    reverse(it,v.end());
    //fl(i,1,m)cout<<v[i]<<" ";
    ll p=1;
    //cout<<(1<<n)<<endl;
    for(ll i=n;i>=1;i--){
        //cout<<p<<endl;
        for(ll j=p;(j-p+1)<=(1<<i);j+=2){
            ll fi=v[j],sec=v[j+1];
            //if(j==1)cout<<fi<<" "<<sec<<endl;
            if(fi==w || sec==w)v.push_back(w);
            else v.push_back(min(fi,sec));
        }
        p+=(1<<i);
    }
    it=v.begin();
    it++;
    reverse(it,v.end());
    fl(i,1,v.size()-1)cout<<v[i]<<" ";
    cout<<endl;
    
}

int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    test
        solve();
    return 0;
}