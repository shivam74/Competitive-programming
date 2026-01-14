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
vector<ll> primeFactors(ll n){
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
    vector<string>b(n+1);
    vector<string>m(n+1);
    fl(i,1,n){
        cin>>b[i];
    }
    fl(i,1,n){
        cin>>m[i];
    }
    string biraj,minaal;
    char ch='0';
    for(ll i=0;i<=10005;i++){
        biraj+=ch;
        minaal+=ch;
    }
    fl(i,1,n){
        string s=b[i];
        int carry=0;
        for(ll i=s.size()-1;i>=0;i++){
            int x=biraj[i]-'0';
            int y=s[i]-'0';
            string result=to_string(x+y+carry);
            if(result.size()>1){
                biraj[i]=s[1];
                carry=s[0];
            }
            else{
                biraj[i]=s[0];
                carry=0;
            }
        } 
        if(carry){
            int x=biraj[s.size()]-'0';
            x++;
            while()
        }
    }
    fl(i,1,n){
        string s=b[i];
        int carry=0;
        for(ll i=0;i<s.size();i++){
            int x=minaal[i]-'0';
            int y=s[i]-'0';
            string result=to_string(x+y+carry);
            if(result.size()>1){
                minaal[i]=s[1];
                carry=1;
            }
            else{
                minaal[i]=s[0];
                carry=0;
            }
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