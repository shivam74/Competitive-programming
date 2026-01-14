// !!!!radha vallabh shri harivansh!!!!

#include <bits/stdc++.h>
using namespace std;
#define nline "\n"
#define int long long 
#define forr(i, a, b) for (int i = a; i < (int)(b); ++i)
const int MOD = (int)(1e9 + 7);



const int NMAX = 1e5 + 5;
int fact[NMAX], invfact[NMAX];



// binary exponentiation
int binpow(int a, int b, int mod) {
    int result = 1;
    a %= mod;
    while (b > 0) {
        if (b & 1)
            result = result * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return result;
}


// modular inverse
int modinv(int a, int mod) {
    return binpow(a, mod - 2, mod);
}


// factorials
void precompute_factorials() {
    fact[0] = invfact[0] = 1;
    for (int i = 1; i < NMAX; i++) {
        fact[i] = fact[i - 1] * i % MOD;
        invfact[i] = modinv(fact[i], MOD);
    }
}


// combinatorics 
int nCr(int n, int r) {
    if (r > n || r < 0) return 0;
    return fact[n] * invfact[r] % MOD * invfact[n - r] % MOD;
}

const int INF = 1e9;



void solve() {
// (i - shift < 0) more left to jump = n - 1 - (i + 1)
    int n, c; cin >> n >> c; 
    vector<vector<int>> dp(n, vector<int> (n, INF)); 
    int b[n], d[n]; 
    forr(i, 0, n) cin >> b[i]; 
    forr(i, 0, n) cin >> d[i];
    forr(i, 0, n) dp[0][i] = b[i] * d[i]; 
    forr(sft, 1, n){
        forr(i, 0, n){
            if(i - sft < 0){
                dp[sft][i] = min(dp[sft-1][i], b[n-sft+i] * d[i]);    
            }
            else dp[sft][i] = min(dp[sft-1][i], b[i-sft] * d[i]); 
        }
    }
    int mini = INT_MAX; 
    forr(sft, 0, n){
        int cost = 0; 
        forr(i, 0, n){
            cost += dp[sft][i]; 
        }
        cost += sft * c; 
        mini = min(mini, cost); 
    }
    
    cout << mini << '\n'; 
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    // precompute_factorials(); 

    int t; cin >> t;
    while (t--) {
        solve();
    }
}