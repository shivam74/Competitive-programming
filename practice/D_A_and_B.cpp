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
    string s;
    cin>>s;
    vector<ll> a(1),b(1);
    fl(i,0,n-1){
        if(s[i]=='a')a.push_back(i+1);
        else b.push_back(i+1);
    }
    ll m1=a.size()/2;
    ll med1=a[m1];
    ll m2=b.size()/2;
    ll med2=b[m2];
    ll cost1=0,cost2=0;
    ll r=med1+1;
    fl(i,m1+1,a.size()-1){
        cost1+=abs(r-a[i]);
        r++;
    }
    ll l=med1-1;
    rl(i,m1-1,1){
        cost1+=abs(l-a[i]);
        l--;
    }
    r=med2+1;
    fl(i,m2+1,b.size()-1){
        cost2+=abs(r-b[i]);
        r++;
    }
    l=med2-1;
    rl(i,m2-1,1){
        cost2+=abs(l-b[i]);
        l--;
    }
    cout<<min(cost1,cost2)<<endl;

}

int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    test
        solve();
    return 0;
}