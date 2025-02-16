#include<bits/stdc++.h>
using namespace std;

double func(vector<int>& sum,int cur, int crd,vector<vector<double>>& ans,vector<tuple<int,double,double>>& vt){
    if(cur == 0) return 0;
    if(crd>=vt.size()) return -1e9;
    if(ans[cur][crd]!=0) return ans[cur][crd];

    for(int i=0; i<= cur; i++)
        if((i|cur)==cur){
            auto [x,y,z] = vt[crd];
            ans[cur][crd] = max(ans[cur][crd],func(sum,cur-i,crd+1,ans,vt)+(sum[i]<x?sum[i]*z/100:sum[i]*y/100));
        }

    return ans[cur][crd];
}

signed main(){
    int t; cin>>t;
    while(t--){
        int n; cin>>n;
        
        vector<tuple<int,double,double>> vt(n);
        for(auto& [x,y,z]: vt) cin>>x>>y>>z;
    
        int e; cin>>e;
        vector<int> vc(e),sum(1<<e,0);
        for(auto& i: vc) cin>>i;

        vector<vector<double>> ans(1<<e,vector<double>(n,0));

        for(int i=0; i<(1<<e); i++)
            for(int j=0; j<e; j++)
                if(i&(1<<j)) sum[i] += vc[j];
             
        cout<<func(sum,(1<<e)-1,0,ans,vt)<<endl;
            
    }
}