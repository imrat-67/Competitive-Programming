#include<bits/stdc++.h>
using namespace std;
int main (){
    int t; cin>>t;
    while(t--){
        int n; cin>>n;
        string s; cin>>s;
        int cnt = count(s.begin(),s.end(),'1');
        bool f = 0;
        for(int i=1; i<n; i++) if(s[i]==s[i-1] and s[i]=='1') f = 1;
        if(cnt%2==1 or(f and cnt==2)) cout<<"NO"<<endl;
        else cout<<"YES"<<endl;
    }
}