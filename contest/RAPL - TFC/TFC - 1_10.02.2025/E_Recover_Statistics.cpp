#include<bits/stdc++.h>
using namespace std;
#define int long long

signed main(){
    int a,b,c; cin>>a>>b>>c;

    vector<int> vc;
    for(int i=0; i<50; i++) vc.push_back(a);
    for(int i=50; i<95; i++) vc.push_back(b);
    for(int i=95; i<99; i++) vc.push_back(c);
    vc.push_back(c+1);

    cout<<vc.size()<<endl;
    for(auto i: vc) cout<<i<<" ";
    cout<<endl;
}

