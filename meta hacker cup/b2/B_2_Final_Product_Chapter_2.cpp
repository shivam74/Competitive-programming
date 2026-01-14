#include <bits/stdc++.h>
using namespace std;

using u64 = unsigned long long;
using u128 = unsigned __int128;
static const u64 MOD = 1000000007ULL;

// -------- modular arithmetic (mod 1e9+7) ----------
u64 mod_pow(u64 a, u64 e) {
    u64 r = 1 % MOD;
    a %= MOD;
    while (e) {
        if (e & 1) r = (u128)r * a % MOD;
        a = (u128)a * a % MOD;
        e >>= 1;
    }
    return r;
}
u64 mod_inv(u64 a) { return mod_pow(a, MOD - 2); }

// -------- Miller-Rabin + Pollard Rho (64-bit safe for B <= 1e14) ----------
u64 mul_mod_u64(u64 a, u64 b, u64 m) { return (u128)a * b % m; }

u64 br_pow(u64 a, u64 d, u64 mod) {
    u64 r = 1 % mod;
    while (d) {
        if (d & 1) r = mul_mod_u64(r, a, mod);
        a = mul_mod_u64(a, a, mod);
        d >>= 1;
    }
    return r;
}

bool isPrime(u64 n) {
    if (n < 2) return false;
    for (u64 p : {2ULL, 3ULL, 5ULL, 7ULL, 11ULL, 13ULL, 17ULL}) {
        if (n % p == 0) return n == p;
    }
    u64 d = n - 1, s = 0;
    while ((d & 1) == 0) { d >>= 1; ++s; }
    auto check = [&](u64 a) {
        if (a % n == 0) return true;
        u64 x = br_pow(a, d, n);
        if (x == 1 || x == n - 1) return true;
        for (u64 i = 1; i < s; ++i) {
            x = mul_mod_u64(x, x, n);
            if (x == n - 1) return true;
        }
        return false;
    };
    // Deterministic bases for 64-bit; this set is more than enough for n <= 1e16
    for (u64 a : {2ULL, 3ULL, 5ULL, 7ULL, 11ULL, 13ULL, 17ULL})
        if (!check(a)) return false;
    return true;
}

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

u64 pollard(u64 n) {
    if ((n & 1ULL) == 0) return 2;
    if (n % 3ULL == 0) return 3;
    uniform_int_distribution<u64> dist(2, n - 2);
    while (true) {
        u64 c = dist(rng);
        u64 x = dist(rng);
        u64 y = x;
        u64 d = 1;
        auto f = [&](u64 v) { return (mul_mod_u64(v, v, n) + c) % n; };
        while (d == 1) {
            x = f(x);
            y = f(f(y));
            u64 diff = x > y ? x - y : y - x;
            d = gcd(diff, n);
        }
        if (d != n) return d;
    }
}

void factor(u64 n, vector<u64>& fac) {
    if (n == 1) return;
    if (isPrime(n)) { fac.push_back(n); return; }
    u64 d = pollard(n);
    factor(d, fac);
    factor(n / d, fac);
}

// Compute C(N - 1 + k, k) mod MOD, with very large N and tiny k (k <= ~46)
u64 comb_Nminus1_plus_k_choose_k(u64 N, int k, const vector<u64>& inv) {
    if (k == 0) return 1;
    u64 base = (N + MOD - 1) % MOD; // (N - 1) mod MOD
    u64 res = 1;
    for (int i = 1; i <= k; ++i) {
        u64 term = (base + i) % MOD; // N - 1 + i
        res = (u128)res * term % MOD;
        res = (u128)res * inv[i] % MOD;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if (!(cin >> T)) return 0;
    for (int tc = 1; tc <= T; ++tc) {
        u64 N, A, B;
        cin >> N >> A >> B;

        // Factorize B
        vector<u64> fac;
        factor(B, fac);
        sort(fac.begin(), fac.end());

        vector<u64> primes;
        vector<int> exps;
        for (size_t i = 0; i < fac.size();) {
            size_t j = i;
            while (j < fac.size() && fac[j] == fac[i]) ++j;
            primes.push_back(fac[i]);
            exps.push_back((int)(j - i));
            i = j;
        }

        // Precompute inverses up to max exponent
        int maxE = 0;
        for (int e : exps) maxE = max(maxE, e);
        if (maxE == 0) { // B == 1
            // Only one sequence: first N product must be 1 (<= A since A >= 1), second N product must be 1
            cout << "Case #" << tc << ": 1\n";
            continue;
        }

        vector<u64> inv(maxE + 1, 1);
        for (int i = 2; i <= maxE; ++i) inv[i] = mod_inv(i);

        // Precompute comb[k] = C(N - 1 + k, k) for k = 0..maxE
        vector<u64> comb(maxE + 1, 1);
        for (int k = 1; k <= maxE; ++k) {
            // C(N - 1 + k, k) = C(N - 1 + (k-1), k-1) * (N - 1 + k) / k
            u64 base = (N + MOD - 1) % MOD; // N - 1 mod MOD
            u64 term = (base + k) % MOD;
            comb[k] = (u128)comb[k - 1] * term % MOD;
            comb[k] = (u128)comb[k] * inv[k] % MOD;
        }

        // For each prime with exponent e, precompute F[k] = comb[k] * comb[e - k] mod MOD
        int m = (int)primes.size();
        vector<vector<u64>> F(m);
        for (int i = 0; i < m; ++i) {
            int e = exps[i];
            F[i].assign(e + 1, 0);
            for (int k = 0; k <= e; ++k) {
                F[i][k] = (u128)comb[k] * comb[e - k] % MOD;
            }
        }

        // Enumerate all choices of exponents x_j with 0..e_j such that P = prod p_j^{x_j} <= A
        u64 ans = 0;
        function<void(int, u128, u64)> dfs = [&](int idx, u128 P, u64 ways) {
            if (idx == m) {
                // valid split -> add multiplicative ways
                ans += ways;
                if (ans >= MOD) ans -= MOD;
                return;
            }
            u64 p = primes[idx];
            int e = exps[idx];
            u128 ppow = 1;
            for (int k = 0; k <= e; ++k) {
                u128 nextP = P * ppow;
                if (nextP > (u128)A) break; // larger k will only increase
                u64 nextW = (u128)ways * F[idx][k] % MOD;
                dfs(idx + 1, nextP, nextW);
                ppow *= (u128)p;
            }
        };
        dfs(0, 1, 1);

        cout << "Case #" << tc << ": " << ans % MOD << "\n";
    }
    return 0;
}