#define ll long long
class Solution {
public:
    int rec(vector<vector<int>>& stations )
    
    int minRefuelStops(int target, int startFuel, vector<vector<int>>& stations) {
        ll n=stations.size();
        vector<ll> v(n+2);
        v[0]=0; v[n-1]=target;
        for(ll i=0;i<n;i++){
            v[i+1]=stations[i][0];
        }
        // i->ith station tak j station lene par kitna fuel bacha hai;
        vector<vector<int>> dp(n+2,vector<int>(n+2));
        dp[0][0]=startFuel;
        for(ll i=0;i<n+2;i++){
            for(ll j=i+1;j<n+2;j++){
                dp[i][j]=-1;
            }
        }
        for(ll i=1;i<n+2;i++){
            for(ll j=0;j<=i;j++){
                dp[i][j]=
            }
        }

        
    }
};