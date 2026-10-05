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
#define setbits(n)  __builtin_popcountll(n)
#define bitsize(n) (63 - __builtin_clzll(n))
#define lcm(a,b) (a/__gcd(a, b)*b)

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

ll modExp(ll a, ll b, ll mod){
     a%=mod;
      ll res=1;              
      while(b){
          if(b & 1){
              res=res*a %mod;
          }
          a=a*a % mod;
          b/=2;
      }
      return res;
}
long long modInverse(long long a, long long mod) {
    return modExp(a, mod - 2, mod);
}


vector<bool> seive_of_eratosthenes(ll n){
     vector<bool> v(n+1,1);
     if (n >= 0) v[0] = false;
     if (n >= 1) v[1] = false;
   
     for (ll i = 2; i * i <= n; i++) {
         if (v[i]) { 
             for (ll j = i * i; j <= n; j += i) {
                 v[j] = false;
             }
         }
     }
     return v;
}


//priority_queue<int, vector<int>, greater<int>> minPQ;

//------------------------Solution starts from here------------------------

// void solve(){
//     ll n , m ; cin>>n>>m ; 
//     vector<vector<ll>> rest(n+1);
//     vector<ll> d1(n+1),d2(n+1);
//     for(int i=0 ; i< m ;i++){
//         vector<ll> v(3); 
//         cin>>v[0]>>v[1]>>v[2];
//         rest[v[1]].push_back(v[2]);
//         rest[v[2]].push_back(v[1]);
//         if(v[0]==1){
//             d1[v[1]]++;
//             d2[v[2]]++;
//         }
//         else{
//             d1[v[1]]++;
//             d2[v[2]]++;
//         }
//     }
//     queue<ll> q;
//     for(ll i=0 ; i< n; i++){
//         if(d1[i]==0 || d2[i]==0){
//             q.push(i);
//         }
//     }
//     vector<ll> ans(n);

//     ll val = 1e9;
//     while(!q.empty()){
//         int node = q.pop();
//         ans[node]=val;
//         if(d1[i]==0){
//             for(int i=0; i<rest[node].size(); i++){
//                 d1[rest[node][i]]--;
//                 if(d1[rest[node][i]]==0){
//                     q.push(rest[node][i]);
//                 }
//             }
//         }
//         else{
//             for(int i=0; i<rest[node].size(); i++){
//                 d2[rest[node][i]]--;
//                 if(d2[rest[node][i]]==0){
//                     q.push(rest[node][i]);
//                 }
//             }
//             ans*=-1;
//         }
//     }
//     for(int i=0; i<n ; i++){
//         if(ans[i]==0){
//             cout<<"NO"<<endl;
//             return;
//         }
//     }
//     for(int i=0; i<n ; i++){
//         cout<<ans[i]<<" ";
//     }
//     cout<<endl;
// }
void solve(){
    ll n, m; 
    cin >> n >> m; 
    
    // Store pairs of {neighbor, restriction_type}
    vector<vector<pair<ll, int>>> rest(n + 1);
    vector<ll> d1(n + 1, 0), d2(n + 1, 0);
    
    for(int i = 0; i < m; i++){
        ll type, u, v; 
        cin >> type >> u >> v;
        
        rest[u].push_back({v, type});
        if(u != v) {
            rest[v].push_back({u, type}); // Prevent duplicate edges on self-loops
        }
        
        if(type == 1){
            d1[u]++;
            if(u != v) d1[v]++;
        } else {
            d2[u]++;
            if(u != v) d2[v]++;
        }
    }
    
    queue<ll> q;
    vector<bool> vis(n + 1, false);
    
    // 1-based indexing as per problem statement
    for(ll i = 1; i <= n; i++){
        if(d1[i] == 0 || d2[i] == 0){
            q.push(i);
            vis[i] = true;
        }
    }
    
    vector<ll> ans(n + 1, 0);
    ll val = 1e9;
    int processed = 0; // Track how many nodes we assign

    while(!q.empty()){
        ll node = q.front(); // Correct way to pop in C++
        q.pop();
        
        processed++;
        
        if(d2[node] == 0){
            ans[node] = val;  // Node is the largest positive
        } else {
            ans[node] = -val; // Node is the largest negative
        }
        
        val--; // Decrease the magnitude for the next element
        
        for(auto edge : rest[node]){
            ll neighbor = edge.first;
            int type = edge.second;
            
            if(vis[neighbor]) continue; // Skip if already processed
            
            // Decrement the correct degree based on the original restriction
            if(type == 1){
                d1[neighbor]--;
            } else {
                d2[neighbor]--;
            }
            
            // If the neighbor is now free to be assigned, push it
            if((d1[neighbor] == 0 || d2[neighbor] == 0) && !vis[neighbor]){
                q.push(neighbor);
                vis[neighbor] = true;
            }
        }
    }
    
    // If we didn't process all n elements, there's a contradiction
    if(processed < n){
        cout << "NO\n";
        return;
    }
    
    // Output valid array
    cout<<"YES"<<endl;
    for(int i = 1; i <= n; i++){
        cout << ans[i] << " ";
    }
    cout << "\n";
}
int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    test
        solve();
    return 0;
}