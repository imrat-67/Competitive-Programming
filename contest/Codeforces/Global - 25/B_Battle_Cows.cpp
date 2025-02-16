#include<bits/stdc++.h>
using namespace std;

int main(){
    int t; cin>>t;
    while(t--){
        int n,k,p; cin>>n>>p;
        deque<int> dq(n);
        for(auto& i: dq) cin>>i;

        function<int(int,int)> lamda = [&](int s,int t){
            for(int i=s; i<n; i++) if(dq[i]>dq[t]) return i;
            return n;
        };

        k = lamda(0,p-1);
        int ans = k-1;
        k = k<p?k:p-1;
        swap(dq[k],dq[p-1]);

        cout<<max(ans,(dq[0] < dq[k]) + lamda(k,k) - k - 1) <<endl;
    }
}