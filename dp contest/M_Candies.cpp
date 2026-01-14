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

vector<ll> primeFactors(ll n) {
    vector<ll> factors;
    while (n % 2 == 0) { factors.push_back(2); n /= 2; }
    for(ll i=3; i*i<=n; i+=2){
        while(n % i == 0){ factors.push_back(i); n /= i; }
    }
    if(n != 1) factors.push_back(n);
    return factors;
}


ll dp[100][100005];
ll mod= 1e9+7;

void solve(){
    ll n,k;
    cin>>n>>k;
    vll v(n);
    for(auto &x: v)cin>>x;
    for(ll i=0;i<=v[0];i++)dp[0][i]=1;
    vll prefix_sum(k+1);
    prefix_sum[0]=1;
    for(ll i=1;i<n;i++){
        for(ll j=1;j<=k;j++)prefix_sum[j]=(prefix_sum[j-1]+dp[i-1][j])%mod;
        for(ll j=0;j<=k;j++){
            // if(j==k && i==2){
            //     cout<<v[i]<<endl;
            //     cout<<prefix_sum[j]<<" "<<prefix_sum[j-v[i]-1]<<endl;
            // }
            if(j>v[i])
               dp[i][j]=(prefix_sum[j]+mod-prefix_sum[j-v[i]-1])%mod;
            else{
            //    if(i==2 && j==k)cout<<"che"<<endl;
               dp[i][j]=prefix_sum[j];
            }
        }

    }
    // for(ll i=0;i<n;i++){
    //     for(ll j=0;j<=k;j++){
    //         cout<<dp[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }
    cout<<dp[n-1][k]<<endl;
}

int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
   // test
        solve();
    return 0;
}