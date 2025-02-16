#include<bits/stdc++.h>
using namespace std;

int main(){
    int t; cin>>t;
    while(t--){
        int n; cin>>n;
        int ar[n]; for(int i=0; i<n; cin>>ar[i++]);

        if(n<3 and abs(ar[0]-ar[1])>1) cout<<"YES"<<endl;
        else cout<<"NO"<<endl;
    }
}