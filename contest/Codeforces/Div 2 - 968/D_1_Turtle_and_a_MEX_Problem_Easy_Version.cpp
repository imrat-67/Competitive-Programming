#include<bits/stdc++.h>
using namespace std;
#define int long long

int mex(vector<int> vc){
    unordered_set<int> st(vc.begin(),vc.end());
    int cnt = 1;
    
    unordered_set<int> :: iterator it = st.begin();
    for(int i=0;; i++){
        if(st.find(i)==st.end()){
            if(!cnt) return i;
            else cnt--;
        }
    }
}

signed main(){
    int t; cin>>t;
    while(t--){
        int n,m; cin>>n>>m;
        
        int mx = 0;
        while(n--){
            int l; cin>>l;
            vector<int> vc(l);
            for(auto &i: vc) cin>>i;

            mx = max(mx,mex(vc));
        }

        if(m<mx) mx += mx*m;
        else mx = mx * mx + (mx+m) * (m-mx+1) / 2;

        cout<<mx<<endl;
    }
}