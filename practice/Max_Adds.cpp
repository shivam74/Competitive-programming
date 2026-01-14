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
#define nl "\n"

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
    ll n,m; cin>>n>>m;
    vll a(n),b(n);
    fl(i,0,n-1)cin>>a[i];
    fl(i,0,n-1)cin>>b[i];
    ll x=0;
    ll y=0;
    ll f1=0;
    ll a1=0;
    fl(i,0,n-1){
        a1=(a[i]-(y+b[i]));
        //cout<<y<<endl;
        x+=max(0ll,a1);
        y=max(a[i],y+b[i]);
    }
    y=0;//f0
    fl(i,0,n-1){
        y=max(a[i],y+b[i]);
    }
    // cout<<x<<endl;
    // cout<<y<<endl;
    ll ans=0;
    if(m<=x ){
        ans=m*y;
        cout<<ans<<endl;
        return;
    }
    else{
        m=y+(m-x);
        //cout<<m<<endl;
        ll sum=(m*(m+1))/2;
        ll sumx=(y*(y+1))/2;
        ll req=sum-sumx;
        ans=x*y+req;
        cout<<ans<<endl;
    }

}

int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    test
        solve();
    return 0;
}