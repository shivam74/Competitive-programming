#include<bits/stdc++.h>
using namespace std;
int32_t main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n,k;
        cin>>n>>k;
        // deque<int> dq;
        string s;
        cin>>s;
        int cnt0 = 0, cnt1 = 0, cnt2 = 0;
        for(int i = 0; i < k; i++)
        {
            if(s[i] == '0') cnt0++;
            else if(s[i] == '1') cnt1++;
            else cnt2++;
        }
        if(n == 1)
        {
            cout<<'-'<<"\n";
            continue;
        }
        if(cnt2 == n)
        {
            for(int i = 0; i < n; i++)
            cout<<"-";
            cout<<"\n";
            continue;
        }
        int right = n - cnt1 + 1;
        int left = cnt0;
        for(int i = 1; i <= n; i++)
        {
            // if(left + cnt2 == right - cnt2 and left + cnt2 == i) cout<<'-';
            if(i <= cnt0) cout<<'-';
            else if(i >= right) cout<<'-';
            else if(i <= cnt0 + cnt2 or i >= right - cnt2) cout<<'?';
            else cout<<'+';
        }
        cout<<"\n";
    }
}
