#include <iostream>
#include <vector>

using namespace std;

// Returns dp array where dp[r] is true if a valid partition of size k % 3 == r exists
vector<bool> dfs(int u, int par, const vector<vector<int>>& adj) {
    bool is_leaf = true;
    // Base combination sum = 0 before processing children
    vector<bool> combined_sums = {true, false, false};

    for (int v : adj[u]) {
        if (v == par) continue;
        is_leaf = false;
        
        vector<bool> child_dp = dfs(v, u, adj);
        vector<bool> next_sums(3, false);

        // Combine possible remainder sums from children
        for (int s = 0; s < 3; ++s) {
            if (!combined_sums[s]) continue;
            for (int c = 0; c < 3; ++c) {
                if (child_dp[c]) {
                    next_sums[(s + c) % 3] = true;
                }
            }
        }
        combined_sums = next_sums;
    }

    vector<bool> dp(3, false);
    if (is_leaf) {
        dp[1] = true; // Shaking this leaf counts as 1
    } else {
        dp = combined_sums; // Option B: split among children
        dp[1] = true;       // Option A: shake node u itself
    }
    return dp;
}

void solve() {
    int n;
    cin >> n;
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<bool> root_dp = dfs(1, 0, adj);

    if (root_dp[0]) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}