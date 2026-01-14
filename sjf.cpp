#include <iostream>
#include <algorithm>
using namespace std;

struct Process{
    int pid;
    int AT;
    int BT;
    int CT;
    int TAT;
    int WT;
};

bool cmp(Process a,Process b){
    return a.BT<b.BT;
}

int main(){
    int n=3;
    Process p[n];
    cout<<"Enter details of Processes :";
    cout<<"\n";

    for(int i=0;i<n;i++){
        p[i].pid=i+1;
        cout<<"Enter AT of Process "<<i+1<<" : ";
        cin>>p[i].AT;
        cout<<"\n";
        cout<<"Enter BT of Process "<<i+1<<" : ";
        cin>>p[i].BT;
        cout<<"\n";
    }
    sort(p,p+n,cmp);
    int currentTime=0;
    for(int i=0;i<n;i++){
        if(currentTime<p[i].AT){
            currentTime=p[i].AT;
        }
        p[i].CT=currentTime+p[i].BT;
        p[i].TAT=p[i].CT-p[i].AT;
        p[i].WT=p[i].TAT-p[i].BT;
    }
    cout<<"PID\tAT\tBT\tCT\tTAT\tWT\n";
    for(int i=0;i<n;i++){
        cout<<"P"<<p[i].pid<<"\t"<<p[i].AT<<"\t"<<p[i].BT<<"\t"<<p[i].CT<<"\t"<<p[i].TAT<<"\t"<<p[i].WT<<"\n";
    }

}