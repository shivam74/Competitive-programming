#include<bits/stdc++.h>
using namespace std;
#define ll long long
vector<ll> hsh(1e6+1);
int main(){
ll n;
cin>>n;
vector<ll> v(n);
for(auto &val:v){
    cin>>val;
  for(ll i=2;i*i<=val;i++){
    if(val%i==0){
        hsh[val/i]++;
        if(i*i!=n)
        hsh[i]++;
    }  
  }
}

ll ans=-1;
for(auto &val:v){
    for(ll i=2;i*i<=val;i++){
      if(val%i==0){
       if(hsh[val/i]>0 || hsh[i]>0){
        ans=max(ans,val/i);
        ans=max(ans,i);
      }
    }
}
if(hsh[1]==n){
    cout<<1<<endl;
}
else{
    cout<<ans<<endl;
}
}
}