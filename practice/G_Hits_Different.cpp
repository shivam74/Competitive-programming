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

ll sum_of_square(ll n){
    return (n*(n+1)*((2*n)+1))/6;
}

void solve(){
    ll n; cin>>n;
    ll x=1;
    ll row=1;
    while(x<n){
        row++;
        x=((row)*(row+1))/2;  
    }
    ll first=n,last=n;
    ll ans=0;
    //cout<<row<<endl;
    while((last-first+1)<row){
        ans+=sum_of_square(last)-sum_of_square(first-1);      
        ll r=((row)*(row+1))/2,l=r-row+1;
        row--;
        ll r1=((row)*(row+1))/2,l1=r1-row+1;
        if(l!=first)l++;
        l1+=first-l;
        if(r!=last)r--;
        r1-=r-last;
        first=l1;
        last=r1;
        //cout<<first<<" "<<last<<endl;
    }
    ll y=((row)*(row+1))/2;
    ans+=sum_of_square(y);
    cout<<ans<<endl;
}

int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    test
        solve();
    return 0;
}