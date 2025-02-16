#include<bits/stdc++.h>
using namespace std;

int main(){
    int t; cin>>t;
    while(t--){
        int n,k; cin>>n>>k;
        int ar[n]; for(int i=0; i<n; cin>>ar[i++]);

        sort(ar,ar+n);
        bool f = ar[1]-ar[0] <= k;
        for(int i=1; i<n-1; i++) f &= ar[i+1] - ar[i] <= k and ar[i] - ar[i-1] <= k;
        
        if(f) for_each(ar,ar+n,[](int& x){cout<<x<<" ";});
        else cout<<"No Solution";

        cout<<endl;
    }
}