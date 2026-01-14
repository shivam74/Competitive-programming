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
    ll l,r;
    cin>>l>>r;
    map<ll,ll> v;
    fl(i,l,r){
        v[i]=-1;
    }
    rl(i,r,l){
        if(v[i]!=-1)continue;
        ll x=i;
        ll b=((x==0)?-1:63-__builtin_clzll(x));
        b++;
        //cout<<b<<" ";
        ll y=(1<<b);
        y-=1;         
        //cout<<y<<endl;
        ll z=y^x;
        if(z<=l and v[z]!=-1){
            v[i]=z;
            v[z]=i;
        }   
    }
    for(ll i=2;i<=31;i++){
        for(ll j=r;j>=l;j--){
            if(__builtin_popcountll(v[j])<i || v[j]!=-1)continue;
            ll x=v[j];
            ll fi=(x==0?-1:63-__builtin_clzll(x));
            ll temp=x;
            temp^=(1<<fi);
            ll fi2=fi;
            ll cnt=1;
            // cout<<fi<<endl;
            while(cnt<i){
                fi2--;
                if((1<<fi2)&x){
                    cnt++;
                }
            }
            //cout<<fi2<<endl;
            fi2=max(0ll,fi2);
            ll y=(1<<fi2);
            y-=1;
            y=(x^y);
            // cout<<y<<endl;
            if(y>=l && v[y]==-1){
                v[y]=x;
                v[x]=y;
            }
        }
    }
    ll ans=0;
    fl(i,l,r){
        ans+=(i|v[i]);
    }
    cout<<ans<<endl;
    fl(i,l,r){
        cout<<v[i]<<" ";
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