#include<bits/stdc++.h>
using namespace std;

signed main(){
    int n,mul=1,mulp=1; cin>>n;
    vector<int> vc(n);

    for(auto& i: vc) cin>>i, i==0?mul*=i:(mul*=i,mulp*=i);

    int z = count(vc.begin(),vc.end(),0);
    for(int i=0; i<n; i++) cout<<(vc[i]==0?z>1?0:mulp:mul/vc[i])<< (i==n-1?"":" ");
}