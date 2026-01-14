#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define INF 5*1e18
#define vll vector<ll>

int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll n;
    cin>>n;
    vector<pair<ll,ll>> v(n);
    ll i=0;
    set<pair<ll,ll>> s;
    for(auto &[a,b] : v){
        cin>>a>>b;
        s.insert({a,i});
        i++;
    }
    vll ans(n);
    ll cur=1;
    while(s.size()!=0){
        auto [fi,id]=*s.begin();
        ll f=fi,idx=id;
        ans[idx]=cur;
        s.erase(s.find({fi,id}));
        while(1){
            auto it1=s.upper_bound({v[idx].second,INF});
            if(it1==s.end())break;
            idx=(*it1).second;
            ans[idx]=cur;
            s.erase(it1);
        }
        cur++;
    }
    cout<<cur-1<<endl;
    for(auto &x:ans){
        cout<<x<<" ";
    }
    return 0;
}