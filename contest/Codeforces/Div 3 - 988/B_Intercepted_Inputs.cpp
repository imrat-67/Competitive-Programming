#include<bits/stdc++.h>
using namespace std;

int main(){
    int t; cin>>t;
    while(t--){
        int n; cin>>n;
        map<int,int> mp;

        for(int i=0; i<n; i++){
            int x; cin>>x;
            mp[x] ++;
        }

        for(auto i: mp){
            int v = (n-2)/i.first;
            if(v*i.first != n-2) continue;
            if(mp.count(v) and ((v==i.first and i.second>1) or (v!=i.first))){
                cout<<v<<" "<<i.first<<endl;
                break;
            }
        }
    }
}