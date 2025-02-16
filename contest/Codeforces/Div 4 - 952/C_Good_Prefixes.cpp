#include<bits/stdc++.h>
using namespace std;
#define int long long

signed main(){
    int t; cin>>t;
    while(t--){
        int n; cin>>n;
        priority_queue<int> pq;
        
        int cnt = 0, sum = 0, x;
        while(n--){
            cin>>x;
            pq.push(x);
            sum += x;
            cnt += (sum - pq.top() == pq.top());
        }

        cout<<cnt<<endl;
    }
}