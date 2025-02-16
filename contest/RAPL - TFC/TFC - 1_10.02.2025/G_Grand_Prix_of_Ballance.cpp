#include<bits/stdc++.h>
using namespace std;

bool cmp(pair<int,int> a,pair<int,int> b){
    if(a.second == b.second) return a.first < b.first;
    return a.second > b.second;
}

int main(){
    int t; cin>>t;
    
    while(t--){
        int n,m,q; cin>>n>>m>>q;
        int vc[m+3] = {0};
        vector<pair<int,int>> vp;
        int pt=m,cg=-1;
        set<int> st;

        while(q--){
            int op; cin>>op;
            
            if(op==1){
                pt = m;
                cin>> cg;
                st.clear();
            }  
            else if(op==2){
                int id, cgx;
                cin>>id>>cgx;
                if(cgx == cg and st.count(id) == 0){
                    vc[id] += pt;
                    pt -= 1;
                    st.insert(id);
                                    }                    
            }
            else {
                int id, cgx;
                cin>>id>>cgx;
                if(cgx == cg){
                    st.insert(id);
                }
            }
        }


        for(int i=1; i<=m; i++) vp.push_back(make_pair(i,vc[i]));
        sort(vp.begin(),vp.end(),cmp);
        for(auto i: vp) cout<<i.first<<" "<<i.second<<endl;

    }
}