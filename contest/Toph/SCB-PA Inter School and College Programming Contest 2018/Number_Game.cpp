#include<bits/stdc++.h>
using namespace std;
#define int long long

const int N = 1e6+7;
int val[N];

int func(int i){
    if(i<N and val[i]) return val[i];
    int v = i==1 ? 0 : 1 + (i&1 ? func(3*i+1) : func(i/2));
    if(i<N) val[i] = v;
    return v;
}

signed main(){

    int t; cin>>t;
    for(int i=1; i<=t; i++){
        int n,m,j,d; cin>>n;
        m = j = d = 0;
        while(n--){
            int x,y; cin>>x>>y;
            x = func(x), y = func(y);
            if(x==y) d++;
            else if(x<y) m++;
            else j++;
        }
    
        cout<<"Game No "<<i<<": Montu "<<m<<", Jhontu "<<j<<", Draw "<<d<<endl;
    }


}