#include<bits/stdc++.h>
using namespace std;
#define int long long

signed main(){
    int t; cin>>t;
    while(t--){
        int n; cin>>n;
        int ar[n]; for(int i=0; i<n; cin>>ar[i++]);

        int v1,v2; v1 = abs(ar[0]), v2 = ar[0];
        
        for(int i=1; i<n; i++){
            v1 = abs(max(abs(v2),v1) + ar[i]);
            v2 = v2 + ar[i];
            v1 = max(v1,abs(v2));
        }

        cout<<v1<<endl;
    }
}