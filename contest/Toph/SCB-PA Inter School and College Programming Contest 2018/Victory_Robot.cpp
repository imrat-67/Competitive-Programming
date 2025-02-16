#include<bits/stdc++.h>
using namespace std;

int main(){
    int t; cin>>t;
    while(t--){
        int n; cin>>n;
        if(n==1971) cout<<"Joy Bangla"<<endl;
        else if(n&1) cout<<"Joy"<<endl;
        else cout<<"Bangla"<<endl;          
    }
}