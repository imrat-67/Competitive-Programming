#include<bits/stdc++.h>
using namespace std;

int main(){
    int t; cin>>t;
    while(t--){
        int n; cin>>n;
        int ar[n]; for(int i=0; i<n; cin>>ar[i++]);

        sort(ar,ar+n);
        cout<<ar[n/2]<<endl;
    }
}