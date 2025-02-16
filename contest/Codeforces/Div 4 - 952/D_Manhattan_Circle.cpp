#include<bits/stdc++.h>
using namespace std;

pair<int,int> pos(valarray<char>* vp,int n,int m,pair<int,int> p,int inc){
    for(int i=p.first; i>=0 and i<n; i+=inc){
        for(int j=p.second; j>=0 and j<m; j+=inc){
            if(vp[i][j]=='#') return {i,j};
        }
    }
    return {0,0};
}

int main(){
    int t; cin>>t;
    while(t--){
        int n,m; cin>>n>>m;
        valarray<char>* vc = new valarray<char>[n];

        for(int i=0; i<n; i++){
            vc[i] = valarray<char>(m);
            for(int j=0; j<m; j++) cin>>vc[i][j];
        }

        auto [x,y]   = pos(vc,n,m,{0,0},1);
        auto [xp,yp] = pos(vc,n,m,{n-1,m-1},-1);

        cout<<(x+xp)/2+1<<" "<<y+1<<endl;
        delete[] vc;
    }
}