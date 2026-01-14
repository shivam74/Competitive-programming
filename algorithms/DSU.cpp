#include <bits/stdc++.h>
using namespace std;

#define ll long long

const ll N = 1e5+7;
ll parent[N];
ll sz[N];

void make(ll v){
    parent[v]=v;
    sz[v]=1;
}

ll find(ll v){
    if(parent[v]==v)return v;
    //path compression
    return parent[v]=find(parent[v]);
}

void Union(ll a,ll b){
    a=find(a);
    b=find(b);
    if(a!=b){
        // union by size
        if(sz[a]<sz[b])
            swap(a,b);
        parent[b]=a;
        sz[a]+=sz[b];       
    }
}

