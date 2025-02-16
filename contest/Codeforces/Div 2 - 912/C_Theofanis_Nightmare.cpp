#include<bits/stdc++.h>
using namespace std;
#define int long long

signed main(){
    int t; cin>>t;
    while(t--){
        int n; cin>>n;
        int ar[n]; for(int i=0; i<n; cin>>ar[i++]);

        int br[n+2] = {0}; br[n] = ar[n-1];
        for(int i=n-1; i>0; i--) br[i] += br[i+1]+ar[i-1];
        
        stack<int> st; st.push(ar[0]);

        for(int i=1; i<n; i++){
            st.push(ar[i]);

            while(st.size() > 1 and st.top()<0){
                int x = st.top(); st.pop();
                if(st.top()*i - i*(st.top()+x)+ br[i+2] < (i+1)*(-x)){
                    int y = st.top(); st.pop();
                    st.push(x+y);
                }
                else{
                    st.push(x);
                    break;
                }
            }
        }

        int sum = 0;
        for(int i = st.size(); i>0; i--){
            int x = st.top(); st.pop();
            sum += i*x;
        }

        cout<<sum<<endl;
    }
}