#include<bits/stdc++.h>
using namespace std; 

int main(){
    int n; cin>>n;
    map<pair<int,int>,int> mp;
    
    for(int i=0; i<n; i++){
        int x,y; cin>>x>>y;
        int gcd = ::gcd(x,y);

        if(gcd) x/= gcd, y/= gcd;
        if(x<0) x = - x, y = - y;
        if( !x) y = abs(y);
        if( !y) x = abs(x);
        if(!x and !y){
            mp[make_pair(0,1)]++;
            mp[make_pair(1,0)]++;
            continue;
        }

        mp[make_pair(x,y)] ++;
    }

    int mx = 0;
    for_each(mp.begin(),mp.end(),[&mx](const pair<pair<int,int>,int>& p){
        mx = max(mx,p.second);
    });

    cout<<mx<<endl;
}