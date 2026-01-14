#include<bits/stdc++.h>
using namespace std;



void solve() {
     int x,y;
     cin>>x>>y;
     int p=0,q=0;
     int cur=0;
     vector<int> numbers;
     while(){
        if(((x & (1<<p)))==1) && ((y & (1<<q))==1){
            cur++;
        }
        else if(((x & (1<<p))==0) && ((y & (1<<q))==0)){
            if(cur>0){
                cur--;
                numbers.push_back(2^p);
            }
        }
        else{
            
        }
     }
}

int main() {
    solve();
return 0;
}
