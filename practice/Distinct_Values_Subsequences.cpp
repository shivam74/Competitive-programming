#include <bits/stdc++.h>
using namespace std;
#define l int64_t
int main(){
    l n; cin>>n;
    map<l,l> c; 
    while(n--){
        l x; cin>>x;
        c[x]++;
    }
    l a=1;
    l m=1e9+7;
    for(auto &x : c){
        a*=x.second+1;
        a%=m;
    }
    cout<<a-1<<'\n';
}