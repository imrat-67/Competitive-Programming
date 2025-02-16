#include<bits/stdc++.h>
using namespace std;
#define int long long

signed main(){

    int t; cin>>t;
    while(t--){
        int n,z=0,id=2,v; cin>>n;
        string s;
        
        while(id <= n and z==0){
            cout<<"? "<<1<<" "<<id<<endl;
            cout.flush();
            cin>>z;
            id++;
        }

        v = z;
        if(z>0) s+='1';
        for(int i=0; i<z; i++) s+='0';
        for(int i=0; i<(id-2-z); i++) s+='1';

        reverse(s.begin(),s.end());

        for(;id<=n; id++){
            cout<<"? "<<1<<" "<<id<<endl;
            cout.flush();
            int x; cin>>x;
            if(x != v){
                s += '1';
                v = x;
            }
            else s += '0', z++;
        }

        if(v==0) s = "IMPOSSIBLE";
        cout<<"! "<<s<<endl;

    }
}