#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void solve() {
    int n;
    cin >> n;

    string s;
    cin >> s;

    if (n == 1) {
        cout << 1 << '\n';
        return;
    }

    // --------------------------------------------------
    // Count A(L,R):
    // move s[L] to R
    // Condition:
    // s[L] != s[L+1] and s[L] != s[R]
    // --------------------------------------------------

    vector<int> suffix(26, 0);

    for (char c : s)
        suffix[c - 'a']++;

    ll A = 0;

    for (int L = 0; L < n - 1; L++) {
        int c = s[L] - 'a';

        // Remove s[L], now suffix contains L+1 ... n-1
        suffix[c]--;

        if (s[L] != s[L + 1]) {
            A += (n - L - 1) - suffix[c];
        }
    }

    // --------------------------------------------------
    // Count B(L,R):
    // move s[R] to L
    // Condition:
    // s[R-1] != s[R] and s[L] != s[R]
    // --------------------------------------------------

    vector<int> prefix(26, 0);

    ll B = 0;

    for (int R = 0; R < n; R++) {
        int c = s[R] - 'a';

        if (R > 0 && s[R - 1] != s[R]) {
            B += R - prefix[c];
        }

        prefix[c]++;
    }

    // --------------------------------------------------
    // Count duplicates where A(L,R) == B(L,R)
    //
    // substring has period 2 and even length
    // --------------------------------------------------

    vector<int> far(n);

    far[n - 1] = n - 1;
    far[n - 2] = n - 1;

    for (int i = n - 3; i >= 0; i--) {
        if (s[i] == s[i + 2])
            far[i] = far[i + 1];
        else
            far[i] = i + 1;
    }

    ll duplicate = 0;

    for (int L = 0; L < n - 1; L++) {

        // If first two characters are equal,
        // transformation is not a new string.
        if (s[L] == s[L + 1])
            continue;

        int maxDist = far[L] - L;

        // Valid distances: 1, 3, 5, ...
        duplicate += (maxDist + 1) / 2;
    }

    ll answer = 1 + A + B - duplicate;

    cout << answer << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--)
        solve();

    return 0;
}