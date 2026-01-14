//submitting again as my previous solution is in queue for long time
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
    ll x,m;
    cin>>x>>m;
     
    auto check=[&](ll mid){
        ll first=-1;
        //cout<<(((x>>63) | 0)^((m>>63)| 0))<<endl;
        ll flag=1;
        rl(i,63,0){
            if((((x>>i) & 1)^((mid>>i)& 1))){
                //cout<<i<<endl;
                first=i;
                break;
            }
        }
        ll ans=mid;
        ll temp=(1ll<<63)-1;
        ll temp2=(1ll<<(first+1))-1;
        temp^=temp2;
        ans&=temp;
        return ans;
    };
    ll ans=-1;
    ll l=x,r=5*1e18;
    while(l<=r){
        ll mid=l+(r-l)/2;
        ll  temp=check(mid);
        //cout<<mid<<" "<<temp<<endl;
        if(temp>m){
            l=mid+1;
        }
        else if(temp<m){
            r=mid-1;
        }
        else{
            ans=mid;
            r=mid-1;
        }
    }
    // cout<<check(1152921504606846976)<<endl;
    cout<<ans<<endl;
}

int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    test
        solve();
    return 0;
}