void solve(){
    ll n;
    cin>>n;
    vll v(n);
    for(ll i=0;i<n;i++) cin>>v[i];
    string s;
    cin>>s;
    string s1(n,'0');

    // leftMin[i] = {min value in [0..i], index of that min}
    vector<pair<ll,ll>> left(n);
    left[0] = {v[0], 0};
    for(ll i=1;i<n;i++){
        if(v[i] < left[i-1].first) left[i] = {v[i], i};
        else left[i] = left[i-1];
    }

    // rightMax[i] = {max value in [i..n-1], index of that max}
    vector<pair<ll,ll>> right(n);
    right[n-1] = {v[n-1], n-1};
    for(ll i=n-2;i>=0;i--){
        if(v[i] > right[i+1].first) right[i] = {v[i], i};
        else right[i] = right[i+1];
    }

    // impossible if first or last are '1'
    if(s[0]=='1' || s[n-1]=='1'){
        cout << -1 << '\n';
        return;
    }

    vector<pair<ll,ll>> ans;

    for(ll i=1;i<=n-2;i++){
        if(s[i]=='1' && s1[i]=='0'){
            // prefix min up to i-1 and suffix max from i+1
            auto leftMin = left[i-1];
            auto rightMax = right[i+1];

            if(leftMin.first < v[i] && v[i] < rightMax.first){
                ll L = leftMin.second;
                ll R = rightMax.second;
                // mark all positions strictly between L and R as covered
                for(ll j = L+1; j <= R-1; j++){
                    // optional check: only mark those strictly between values if needed
                    s1[j] = '1';
                }
                // store 1-based indices as your code did
                ans.push_back({L+1, R+1});
            } else {
                // cannot satisfy this '1'
                cout << -1 << '\n';
                return;
            }
        }
    }

    // final check: every '1' in s must be marked in s1
    for(ll i=0;i<n;i++){
        if(s[i]=='1' && s1[i]=='0'){
            cout << -1 << '\n';
            return;
        }
    }

    cout << ans.size() << '\n';
    for(auto &p : ans) cout << p.first << ' ' << p.second << '\n';
}
