#include<bits/stdc++.h>
using namespace std;
#define int long long

signed main(){
    int t; cin>>t;
    while(t--){
        int h,p,d; cin>>h>>p>>d;
        
        vector<tuple<int,int,bool>> vc;
        for(int i=0; i<h; i++){
            int x,y; cin>>x>>y;
            vc.push_back(make_tuple(x,y,1));
        }

        for(int i=0; i<p; i++){
            int x,y; cin>>x>>y;
            vc.push_back(make_tuple(x,y,0));
        }

        sort(vc.begin(),vc.end());

        priority_queue<int> pq;
        int psum = 1, ans = 1e9;
        for(auto i: vc){
            //cout<<get<0>(i)<<" "<<get<1>(i)<<" "<<get<2>(i)<<endl;
            if(get<2>(i)){
                int gap = get<1>(i) - get<0>(i) + 2 ;
                while(not pq.empty() and psum < gap) psum += pq.top(), pq.pop();
                if(psum < gap){
                    ans = -1;
                    break;
                }
            }
            else pq.push(get<1>(i));
            //cout<<"size: "<<pq.size()<<" "<<psum<<endl;
        }

        ans = min(ans,p-(int)pq.size());
        cout<<ans<<endl;
    }
}