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
//s.find_by_order(i) (i->[0-(n-1)]) it give the iterator of i'th element in the set
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

ll mod = 998244353;
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

long long nCr(int n, int r) {
    if (r < 0 || r > n) return 0;
    if (r == 0 || r == n) return 1;
    if (r > n / 2) r = n - r;
    long long result = 1;
    for (int i = 1; i <= r; ++i) {
        result *= (n - i + 1);
        result /= i;
    }
    return result;
}

ll fact(ll x){
    ll ans=1;
    for(ll i=1;i<=x;i++){
        ans=((ans%mod)*i)%mod;
    }
    return ans;
}

void solve(){
    ll n; cin>>n;
    vll v(n);
    ll x; cin>>x;
    fl(i,0,n-1)cin>>v[i];
    if(n==1){
        cout<<1<<endl;
        return;
    }
    sort(v.begin(),v.end());
    ll r1=0,r2=0;
    ll mx=*max_element(v.begin(),v.end());
    for(ll i=0;i<n;i++){
        r1+=mx-v[i];
        if(v[i]<mx)r2+=mx-v[i]-1;
    }
    //cout<<r1<<" "<<r2<<endl;
    if(x>=r1){
        x-=r1;
        x%=n;
        ll N=n,R=x;
        ll ans=nCr(N,R)%mod;
        ans=(ans*fact(x))%mod;
        ans=ans*fact(n-x)%mod;
        cout<<ans<<endl;
        return;
    }
    else if(x>=r2){
        x-=r2;
        ll cnt=0;
        for(ll i=0;i<n;i++){
            if(v[i]!=mx)cnt++;
        }
        ll N=cnt,R=x;
        ll ans=nCr(N,R)%mod;
        ans=(ans*fact(n-cnt+x))%mod;
        ans=ans*fact(cnt-x)%mod;
        cout<<ans<<endl;
        return;
    }
    else{
        map<ll,ll> mp;
        for(auto &x:v){
            mp[x]++;
        }
        if(v[n-1]-v[0]>1){
            cout<<0<<endl;
            return;
        }
        else{
            ll ans=1;
            for(auto &x:mp){
                ans=(ans*fact(x.second))%mod;
            }
            cout<<ans<<endl;
            return;
        }
    }
}

int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    test
        solve();
    return 0;
}