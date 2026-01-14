#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define INF 5*1e18
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

// Ordered Set Template (Ordered multiset)
//ordered_set s;
//s.order_of_key(x) it give no. of elements less than x
//s.find_by_order(i) it give the iterator of i'th element in the set
typedef tree<
    long long, //pii(pair<ll,ll>
    null_type,
    less<long long>,//less<pii>
    rb_tree_tag,
    tree_order_statistics_node_update
> ordered_set;//ordered_multiset


//some reminders....
//if stuck change the perpective of finding answers
//for maximizing/minizing think on bs on answers
//in bits manupulation check long long errors

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
    ll n;
    cin>>n;
    vll a(n),b(n);
    fl(i,0,n-1)cin>>a[i];
    fl(i,0,n-1)cin>>b[i];
    auto fun=[&](double t){
        double l=-1*INF,r=1*INF;
        ll flag=1;
        for(int i=0;i<n;i++){
            if(t<b[i]){
                flag=0;
                break;
            }
            l=max(a[i]-(t-b[i])*1.0,l);
            r=min(a[i]+(t-b[i])*1.0,r);
            if(r<l){
                flag=0;
                break;
            }
        }
        if(flag){
            return true;
        }
        else return false;
    };

    double l=0,r=INF;
    double ans=-1;
    while(l<r){
        double mid=l+(r-l)/2;
        if(fun(mid)){
            ans=mid;
            r=mid-.0000001;
        }
        else{
            l=mid+.0000001;
        }
    }
    l=-1*INF,r=1*INF;
    ll flag=1;
    for(int i=0;i<n;i++){
        l=max(a[i]-(ans-b[i]),l);
        r=min(a[i]+(ans-b[i]),r);
    }
    double ansm=(l+r)/2.0;
    cout<<fixed<<setprecision(7);
    cout<<ansm<<endl;
}

int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    test
        solve();
    return 0;
}