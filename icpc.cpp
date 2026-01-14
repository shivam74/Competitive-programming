// ============================================================================ //
// ||                                                                        || //
// ||                                                                        || //
// ||                            Author Roshan                               || //
// ||                                                                        || //
// ||                                                                        || //
// ============================================================================ //

#include <bits/stdc++.h>
using namespace std;
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
// using namespace __gnu_pbds;
// freopen("abbreviation.in", "r", stdin);
// freopen("abbreviation.out", "w", stdout);

//--------------------------------------------------------------------------------------------------------------------------------------
#pragma GCC optimize("03")
#define Roshan                  \
    cin.sync_with_stdio(false); \
    cin.tie(0);                 \
    cout.tie(0)
#define uint unsigned long long
#define vi vector<int>
#define vvi vector<vi>
#define vb vector<bool>
#define vvb vector<vb>
#define vpp vector<pair<int, int>>
#define fr(i, n) for (int i = 0; i < (n); i++)
#define rep(i, a, n) for (int i = (a); i <= (n); i++)
#define nl cout << endl
// #define all(v) v.begin(), v.end()
#define sz(v) (int)(v.size())
#define srt(v) sort(v.begin(), v.end())         // sort
#define mxe(v) *max_element(v.begin(), v.end()) // find max element in vector
#define mne(v) *min_element(v.begin(), v.end()) // find min element in vector
#define unq(v) v.resize(distance(v.begin(), unique(v.begin(), v.end())));
#define int long long
#define roundUp(a, b) ((a + b - 1) / b)
#define all(x) (x).begin(), (x).end()
#define allr(x) (x).rbegin(), (x).rend()
#define Endl '\n'
const int INF = 1e18;
int MOD = 1e9 + 7;
// int MOD = 1e9 + 7;
//--------------------------------------------------------------------------------------------------------------------------------------
// #define ll long long
const int N = 1000001;
// Use Binomial(n, r, mod) instead of nCr

// array to store inverse of 1 to N
int factorialNumInverse[N + 1];

// array to precompute inverse of 1! to N!
int naturalNumInverse[N + 1];

// array to store factorial of first N numbers
int fact[N + 1];

// Function to precompute inverse of numbers
void InverseofNumber(int p)
{
    naturalNumInverse[0] = naturalNumInverse[1] = 1;
    for (int i = 2; i <= N; i++)
        naturalNumInverse[i] = naturalNumInverse[p % i] * (p - p / i) % p;
}
// Function to precompute inverse of factorials
void InverseofFactorial(int p)
{
    factorialNumInverse[0] = factorialNumInverse[1] = 1;

    // precompute inverse of natural numbers
    for (int i = 2; i <= N; i++)
        factorialNumInverse[i] = (naturalNumInverse[i] * factorialNumInverse[i - 1]) % p;
}

// Function to calculate factorial of 1 to N
void factorial(int p)
{
    fact[0] = 1;

    // precompute factorials
    for (int i = 1; i <= N; i++)
    {
        fact[i] = (fact[i - 1] * i) % p;
    }
}

// Function to return nCr % p in O(1) time
int Binomial(int N, int R, int p)
{
    // n C r = n!*inverse(r!)*inverse((n-r)!)
    int ans = ((fact[N] * factorialNumInverse[R]) % p * factorialNumInverse[N - R]) % p;
    return ans;
}

//--------------------------------------------------------------------------------------------------------------------------------------

uint power(int x, int y, int p = MOD)
{
    unsigned long long res = 1;

    x = x % p;
    while (y > 0)
    {

        if (y & 1)
            res = (res * x) % p;

        y = y >> 1;
        x = (x * x) % p;
    }
    return res;
}
int mod_sub(int a, int b, int m = MOD)
{
    a = a % m;
    b = b % m;
    return (((a - b) % m) + m) % m;
}
//--------------------------------------------------------------------------------------------------------------------------------------
int moduloMultiplication(int a, int b, int mod)
{
    int res = 0;
    a %= mod;
    while (b)
    {
        if (b & 1)
            res = (res + a) % mod;
        b >>= 1;
    }
    return res;
}
//--------------------------------------------------------------------------------------------------------------------------------------

int toInt(string s)
{
    int res;
    stringstream ss;
    ss << s;
    ss >> res;
    return res;
}
string toString(int n)
{
    stringstream ss;
    ss << n;
    return ss.str();
}

//--------------------------------------------------------------------------------------------------------------------------------------

int mex(vi &arr)
{
    int n = arr.size();
    unordered_map<int, int> mp;
    for (int i = 0; i < n; i++)
    {
        mp[arr[i]]++;
    }
    for (int i = 0; i <= n + 1; i++)
    {
        if (mp[i] == 0)
        {
            return i;
        }
    }
    return n + 1;
}

//--------------------------------------------------------------------------------------------------------------------------------------

bool isPalindrome(string &s)
{
    int i = 0;
    int j = s.size() - 1;
    while (i < j)
    {
        if (s[i] != s[j])
        {
            return false;
        }
        i++, j--;
    }
    return true;
}

//--------------------------------------------------------------------------------------------------------------------------------------

uint modInverse(int n, int p = MOD)
{ // using fermats little thm. [p needs to be prime which is mostly the case as mod value generally is 1e9+7]
    return power(n, p - 2, p);
}

//--------------------------------------------------------------------------------------------------------------------------------------

int gcd(int a, int b) { return a ? gcd(b % a, a) : b; }
int lcm(int a, int b) { return (a * b) / gcd(a, b); }

//--------------------------------------------------------------------------------------------------------------------------------------

uint nCr(int n, int r, int p = MOD)
{ // faster calculation..
    if (n < r)
        return 0;

    if (r == 0)
        return 1;

    vector<int> fac(n + 1, 0);
    fac[0] = 1;
    for (int i = 1; i <= n; i++)
        fac[i] = (fac[i - 1] * i) % p;

    return (fac[n] * modInverse(fac[r], p) % p * modInverse(fac[n - r], p) % p) % p;
}
// Get Divisor
vector<int> getDivisors(int n)
{
    vector<int> divisors;

    for (int i = 1; i * i <= n; i++)
    {
        if (n % i == 0)
        {
            divisors.push_back(i); // Add i
            if (i != n / i)
                divisors.push_back(n / i); // Add n/i (only if different)
        }
    }

    sort(divisors.begin(), divisors.end()); // Sorting for ordered output
    return divisors;
}
//--------------------------------------------------------------------------------------------------------------------------------------

template <typename typC, typename typD>
istream &operator>>(istream &cin, pair<typC, typD> &a) { return cin >> a.first >> a.second; }
// typedef tree<int, null_type, less_equal<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
template <typename typC>
istream &operator>>(istream &cin, vector<typC> &a)
{
    for (auto &x : a)
        cin >> x;
    return cin;
}
template <typename typC, typename typD>
ostream &operator<<(ostream &cout, const pair<typC, typD> &a) { return cout << a.first << ' ' << a.second; }
template <typename typC, typename typD>
ostream &operator<<(ostream &cout, const vector<pair<typC, typD>> &a)
{
    for (auto &x : a)
        cout << x << endl;
    return cout;
}
template <typename typC>
ostream &operator<<(ostream &cout, const vector<typC> &a)
{
    int n = a.size();
    if (!n)
        return cout;
    cout << a[0];
    for (int i = 1; i < n; i++)
        cout << ' ' << a[i];
    return cout;
}
struct FenwickTree
{
    vector<int> fenw;
    int n;
    FenwickTree(int _n) : n(_n)
    {
        fenw.assign(n + 2, 0);
    }
    void update(int i, int val)
    {
        for (; i <= n; i += i & (-i))
        {
            fenw[i] = (fenw[i] + val) % MOD;
        }
    }
    int query(int i)
    {
        int res = 0;
        for (; i > 0; i -= i & (-i))
        {
            res = (res + fenw[i]) % MOD;
        }
        return res;
    }
};
//--------------------------------------------------------<- Code Form Here ->---------------------------------------------------------------------

void CoderRoshan()
{
    int n;
    cin >> n;
    string s;
    cin >> s;
    vector<int> ans(n + 1);
    iota(all(ans), 0);
    int f = 1;
    int i = 0;
    while (i < n)
    {
        if (s[i] == '0')
        {
            int j = i;
            while (j < n && s[j] == '0')
                j++;
            if (j - i == 1)
            {
                cout << "NO" << Endl;
                return;
            }
            for (int k = i + 1; k < j; k++)
            {
                ans[k] = k + 1;
            }
            ans[j] = i + 1;
            i = j;
        }
        else
        {
            i++;
        }
    }
    cout << "YES" << Endl;
    for (int i = 1; i <= n; i++)
    {
        cout << ans[i] << " ";
    }
    cout << Endl;
}

int32_t main()
{
    Roshan;
    int t;
    cin >> t;
    // t = 1;
    while (t--)
    {
        CoderRoshan();
    }
    return 0;
}