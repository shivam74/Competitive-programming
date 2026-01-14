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

ll rec(ll l,ll r){
    if(r-l==1){
        cout<<l<<" "<<r<<endl;
        ll x;
        cin>>x;
        return x;
    }
    if(r-l==0)return 0;
    ll mid=(r+l)/2;
    if((mid-l+1)%2!=0)mid++;
    ll f=rec(l,mid);
    if(f==1)return 1;
    ll s=rec(mid+1,r);
    if(s==1)return 1;
    for(ll i=l;i<=mid;i++){
        for(ll j=mid+1;j<=r;j++){
            cout<<i<<" "<<j<<endl;
            ll x ;
            cin>>x;
            if(x==1){
                return x;
            }
        }
    }
    return 0;
}
ll cnt=0;
void ask(ll n){
    for(ll i=2;i<=n;i=i*2){
        for(ll j=1;j<=n;j+=i){
            for(ll k=j;k-j+1<=i/2;k++){
                for(ll l=i/2+j;l-j+1<=i && l<=n;l++){
                    cnt++;
                    if(k==3 && l==7)cout<<cnt<<endl;
                    cout<<k<<" "<<l<<endl;
                    ll x;
                    cin>>x; 
                    if(x==1){
                        cout.flush();
                        return;
                    }
                }
            }
        }
    }
    ll x=2;
    while(x*2<=n){
        x*=2;
    }
    for(ll i=1;i<=x;i++){
        for(ll j=x+1;j<=n;j++){
            cnt++;
            if(i==3 && j==7)cout<<cnt<<endl;
            cout<<i<<" "<<j<<endl;
            ll x;
            cin>>x; 
            if(x==1){
                cout.flush();
                return;
            }
        }
    }
}

void solve(){
    ll n;
    cin>>n;
    ask(n);
    cout.flush();
    cout<<cnt<<endl;
}

int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    test
        solve();
    return 0;
}