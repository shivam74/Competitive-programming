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


//some reminders....
//if stuck change the perpective of finding answers
//for maximizing/minizing think on bs on answers
//in bits manupulation check long long errors

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
//------------------------Solutions starts from here------------------------

void solve(){
    ll n,k;
    cin>>n>>k;
    string s,t;
    cin>>s>>t;
    
    vll v(n);
    fl(i,0,n-1)v[i]=i;
    vll ans(n);
    ll p=n-1,q=n-1;
    while(p>=0){
        if(p>q){p--;}
        else if(t[q]==s[p]){
            ans[q]=p;
            q--;
        }
        else{
            p--;
        }
    }
    if(q>=0){
        cout<<-1<<endl;
        return;
    }
    ll k1=0;
    vector<vector<ll>> final;
    if(v==ans){
        cout<<0<<endl;
        return;
    }
    while(k1<=k){
        for(ll i=n-1;i>=0;i--){
            if(v[i]!=ans[i]){
                v[i]=v[i-1];
            }
        }
        final.push_back(v);
        k1++;
        if(v==ans){
            break;
        }
    }
    if(k1>k){
        cout<<-1<<endl;
        return;
    }
    cout<<k1<<endl;
    for(ll i=0;i<final.size();i++){
        for(auto &x:final[i]){
            cout<<s[x];
        }
        cout<<endl;
    }
}

int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    test
        solve();
    return 0;
}