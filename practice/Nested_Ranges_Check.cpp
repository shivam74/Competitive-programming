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

// int n;

// void solve(vector<vector<int>> ranges) {
//     vector<int> check(n + 1);

//     int pos = 0;
//     for (auto r : ranges) {
//         if (pos >= -r[1]) {
//             check[r[2]] = 1;
//         }
//         pos = max(pos, -r[1]);
//     }

//     for (int i = 1; i <= n; i++) {
//         cout << check[i] << " ";
//     }
//     cout << "\n";
// }

// int main() {
//     cin >> n;

//     vector<vector<int>> ranges1;
//     vector<vector<int>> ranges2;

//     for (int i = 1; i <= n; i++) {
//         int x, y;
//         cin >> x >> y;
//         ranges1.push_back({y, -x, i});
//         ranges2.push_back({x, -y, i});
//     }

//     sort(ranges1.begin(), ranges1.end());
//     sort(ranges2.begin(), ranges2.end());

//     solve(ranges1);
//     solve(ranges2);
// }

void solve(){
    ll n; cin>>n;
    //no duplicate pair
    vector<pair<ll,ll>> v(n);
    vll a(n),b(n);
    multiset<ll> s;
    fl(i,0,n-1){
        cin>>v[i].first>>v[i].second;
        a[i]=v[i].first;
        b[i]=v[i].second;
        s.insert(v[i].second);
    } 
    map<pair<ll,ll>,ll> ans1,ans2;
    sort(all(v),[](pair<ll,ll> &f,pair<ll,ll> &s){
        if(f.first==s.first)return f.second>s.second;
        else{
            return f.first<s.first;
        }
    }); 
    // Is there any interval to the right with end <= current_end
    fl(i,0,n-1){
        s.erase(s.find(v[i].second));
        auto it = s.upper_bound(v[i].second);
        if(s.empty() || it==s.begin())ans1[{v[i].first,v[i].second}]=0;
        else{
            ans1[{v[i].first,v[i].second}]=1;
        }
    }
    s.clear();
    // Is there any interval to the left with end >= current_end
    fl(i,0,n-1){
        if(s.empty())ans2[{v[i].first,v[i].second}]=0;
        else{
            auto it=s.lower_bound(v[i].second);
            if(it!=s.end())ans2[{v[i].first,v[i].second}]=1;
            else ans2[{v[i].first,v[i].second}]=0;
        }
        s.insert(v[i].second);
    }
    fl(i,0,n-1){
        cout<<ans1[{a[i],b[i]}]<<" ";
    }
    cout<<endl;
    fl(i,0,n-1){
        cout<<ans2[{a[i],b[i]}]<<" ";
    }

}

int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //test
        solve();
    return 0;
}