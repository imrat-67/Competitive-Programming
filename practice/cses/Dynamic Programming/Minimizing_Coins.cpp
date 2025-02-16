#include<bits/stdc++.h>
using namespace std;
 
int main(){
    int n,m; cin>>n>>m;
    int ar[n],br[m+1];
 
    memset(br,-1,sizeof(br));
    generate(ar,ar+n,[](){int x; cin>>x; return x;});
    fill(br,br+m+1,1e9);
    br[0] = 0;
 
    for(int i=0; i<=m; i++){
        for(int j=0; j<n; j++){
            int v = i-ar[j];
            if(v<0) continue;
            else br[i] = min(br[i],br[v]+1);
        }
    }
 
    cout<<(br[m]==1e9?-1:br[m])<<endl;
}