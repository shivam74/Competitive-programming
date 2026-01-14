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
    ll a=0,b=0;
    map<ll,set<ll>> m;
    m[b-a].insert(n);
    rl(i,n-1,0){
        if(s[i]=='a'){
            a++;
        }
        else{
            b++;
        }
        m[b-a].insert(i);
    }
    a=0,b=0;
    ll ans=INT_MAX;
    // for(auto &x:m){
    //     //cout<<x.first<<endl;
    //     //sort(x.second.begin(),x.second.end());
    //     // for(auto &y:x.second){
    //     //     cout<<y<<" ";
    //     // }
    //     // cout<<endl;
    // }
    fl(i,0,n-1){

        if(m.find(a-b)!=m.end()){
            //sort(m[a-b].begin(),m[a-b].end());
            auto it=lower_bound(m[a-b].begin(),m[a-b].end(),i);
            if(it!=m[a-b].end()){
                ll x=*it;
                ans=min(ans,(x-i));
                //cout<<i<<" "<<x<<endl;
            }
        }
        if(s[i]=='a'){
            a++;
        }
        else{
            b++;
        }
    }
    // if(m.find(a-b)!=m.end()){
    //         ans=min(ans,(m[a-b]-n));
    //     }
    if((ans)>=n){
        cout<<-1<<endl;
    }
    else{
        cout<<(ans)<<endl;
    }
}

int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    test
        solve();
    return 0;
}