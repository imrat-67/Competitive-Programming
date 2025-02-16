#include<bits/stdc++.h>
using namespace std;
#define ing long long

bool is_square(string s){
    int p = stoll(s), rp = sqrt(p);
    return s[0]!='0' and  rp * rp == p;
}

signed main(){
    int t; cin>>t;
    while(t--){
        string s,tm; cin>>s;
        int n = s.size(), mn = 1e9; 
        
        for(int i=1; i<(1<<n); i++){
            for(int j=0; j<n; j++)
                if(i&(1<<j)) tm += s[j];
            
            if(is_square(tm)) mn = min(mn,n -__popcount(i));
            tm.clear();
        }

        cout<<(mn==1e9?-1:mn)<<endl;
        
    }
}