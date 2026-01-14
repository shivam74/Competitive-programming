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
 
 void solve(ll t){
    ll N; 
    cin >> N;
    vector<uint32_t> pref(N + 1);
    pref[0] = 0;
    fl(i,1,N) {
        uint32_t x; 
        cin >> x;
        pref[i] = pref[i - 1] ^ x;
    }
    sort(pref.begin(), pref.end());
    __int128 n = N;
    unsigned ll total = (unsigned ll)((n * (n + 1) * (n + 2)) / 6);
    
    unsigned ll sub = 0;
    for (size_t i = 0; i < pref.size(); ) {
        size_t j = i + 1;
        while (j < pref.size() && pref[j] == pref[i]) ++j;
        unsigned ll m = (unsigned ll)(j - i);
        if (m >= 2) {
            __int128 tmp = (__int128)m * (m - 1) * (m + 1) / 6; // m(m-1)(m+1)/6
            sub += (unsigned ll)tmp;
        }
        i = j;
    }
    unsigned ll ans = total - sub;
    cout << "Case #" << t<< ": " << ans << "\n";
 }
 
 int32_t main(){
     ios_base::sync_with_stdio(false);
     cin.tie(NULL);
     ll t;
     cin>>t;
     fl(i,1,t)
         solve(i);
     return 0;
 }