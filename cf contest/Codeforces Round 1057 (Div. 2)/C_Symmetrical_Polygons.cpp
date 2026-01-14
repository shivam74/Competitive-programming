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
    vll v(n+1);
    map<ll,ll> m;
    fl(i,1,n){
        cin>>v[i];
        m[v[i]]++;
    }
    vll s;
    ll total=0,peri=0;
    for(auto &x : m){
        ll md=(x.second%2);
        if(md==1)s.push_back(x.first);
        total+=x.second-md;
        peri+=(x.second-md)*x.first;
    }
    //cout<<peri<<endl;
    sort(s.rbegin(),s.rend());
    ll flag=1;
    for(ll i=0;i+1<s.size();i++){       
        ll mni=s[i+1];
        ll mxi=s[i];
        if(peri+mni>mxi){
            peri+=(mxi+mni);
            total+=2;
            flag=0;
            break;
        }
    }
    // cout<<flag<<endl;
    if(flag && s.size()>=1){
        if(peri>s[s.size()-1]){
            // cout<<"check"<<endl;
            peri+=s[s.size()-1];
            total+=1;
        }
    }
    // cout<<total<<endl;
    if(total>=3){
        cout<<peri<<endl;
    }
    else{
        cout<<0<<endl;
    }
}

int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    test
        solve();
    return 0;
}