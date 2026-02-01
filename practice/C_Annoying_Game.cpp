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

//------------------------Solution starts from here------------------------

void solve(){
    ll n,turns;
    cin>>n>>turns;
    vll v(n),b(n);
    fl(i,0,n-1){
        cin>>v[i];
    }
    fl(i,0,n-1){
        cin>>b[i];
    }
    // ll l=-1,r=-1;
    // ll sum=0;
    // ll tar=LLONG_MIN;
    // ll cur=-1;
    vll L(n),R(n);

    L[0]=v[0];
    fl(i,1,n-1){
        if(L[i-1]>0)L[i]=L[i-1]+v[i];
        else L[i]=v[i];
    }
    R[n-1]=v[n-1];
    rl(i,n-2,0){
        if(R[i+1]>0)R[i]=R[i+1]+v[i];
        else R[i]=v[i];
    }
    // fl(i,0,n-1){
    //     cout<<L[i]<<" ";
    // }
    // cout<<nl;
    // fl(i,0,n-1){
    //     cout<<R[i]<<" ";
    // }
    // cout<<nl;
    ll ans=LLONG_MIN;
    if(turns%2==0){
        fl(i,0,n-1){
            ans=max(ans,L[i]+R[i]-v[i]);
        }
    }
    else {
        fl(i,0,n-1){
            ans=max(ans,L[i]+R[i]+b[i]-v[i]);
        }
    }
    cout<<ans<<endl;
    // for(ll i=0;i<n;i++){
    //     if(i==0){
    //         sum+=v[i];
    //     }
    //     else{
    //         if(sum+v[i]>0){
    //             sum+=v[i];
    //         }
    //         else{
    //             sum=v[i];
    //         }
    //     }
    //     tar=max(tar,sum);
    // }
    // if(turns%2==0){
    //     cout<<tar<<endl;
    //     return;
    // }
    // map<ll,ll> pre;
    // pre[v[0]]=0;
    // sum=0;
    // for(ll i=0;i<n;i++){
    //     sum+=v[i];
    //     ll req=tar-sum;
    //     req*=-1;
    //     if(req==0){
    //         l=0;
    //         r=i;
    //     }
    //     else{
    //         if(pre.find(req)!=pre.end()){
    //             if(r-l+1<=i-pre[req]){
    //                 l=pre[req]+1;
    //                 r=i;
    //             }
    //         }
    //     }
    //     if(pre.find(sum)==pre.end()){
    //         pre[sum]=i;
    //     }
    // }
    // //cout<<l<<" "<<r<<nl;
    // if(l==0 && r==n-1){
    //     ll x = *max_element(b.begin(),b.end());    
    //     cout<<max(tar,tar+x)<<nl;
    //     return;
    // }
    // else if(l==0){
    //     ll preR;
    //     ll maxR;
    //     preR=v[r+1];
    //     maxR=b[r+1];
    //     ll y=preR+maxR;
    //     fl(i,r+2,n-1){
    //         preR=(preR+v[i]);
    //         maxR=max(b[i],maxR);
    //         y=max(y,preR+maxR);
    //     }
    //     ll x = *max_element(b.begin(),b.begin()+r+1); 
    //     x= max(x,y);
    //     cout<<max(tar,tar+x)<<nl;
    //     return; 
    // }
    // else if(r==n-1){
    //     //cout<<"cje"<<endl;
    //     ll preL;
    //     ll maxL;
    //     preL=v[l-1];
    //     maxL=b[l-1];
    //     ll y=preL+maxL;
    //     rl(i,l-2,0){
    //         preL=(preL+v[i]);
    //         maxL=max(b[i],maxL);
    //         y=max(y,preL+maxL);
    //     }
    //     //cout<<y<<endl;
    //     ll x = *max_element(b.begin()+l,b.end()); 
    //     x= max(x,y);
    //     cout<<max(tar,tar+x)<<nl;
    //     return; 
    // }
    // else{
    //     ll preL;
    //     ll maxL;
    //     preL=v[l-1];
    //     maxL=b[l-1];
    //     ll y=preL+maxL;
    //     rl(i,l-2,0){
    //         preL=(preL+v[i]);
    //         maxL=max(b[i],maxL);
    //         y=max(y,preL+maxL);
    //     }
    //     ll preR;
    //     ll maxR;
    //     preR=v[r+1];
    //     maxR=b[r+1];
    //     ll y1=preR+maxR;
    //     fl(i,r+2,n-1){
    //         preR=(preR+v[i]);
    //         maxR=max(b[i],maxR);
    //         y1=max(y1,preR+maxR);
    //     }
    //     ll x = *max_element(b.begin()+l,b.begin()+r+1); 
    //     x = max(x,max(y,y1));
    //     cout<<max(tar,tar+x)<<nl;
    //     return;
    // }
}

int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    test
        solve();
    return 0;
}