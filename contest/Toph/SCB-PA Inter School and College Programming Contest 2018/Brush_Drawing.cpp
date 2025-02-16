#include<bits/stdc++.h>
using namespace std;
#define double long double
const double pi = 3.141592653589;

int main(){
    int t; cin>>t;
    vector<pair<int,int>> ar[360];
    while(t--){
        int n; cin>>n;
        for_each(ar,ar+360,[](vector<pair<int,int>>& vp){ vp.clear();});

        while(n--){
            int d,r,x,y; cin>>d>>r>>x>>y;
            for(int i=x; i<y; i++) ar[i].push_back(make_pair(r,r+d));
        }

        double area = 0;
        for_each(ar,ar+360,[&area](vector<pair<int,int>>& vp){
                if(!vp.empty()){ 
                    sort(vp.begin(),vp.end());

                    pair<int,int> p = vp.front();
                    vector<pair<int,int>> vc;
                    
                    for(int i=1; i<vp.size(); i++){
                        if(vp[i].first>p.second) vc.push_back(p), p = vp[i];
                        else p.second = max(p.second,vp[i].second);
                    }

                    vc.push_back(p);

                    for_each(vc.begin(),vc.end(),[&area](const pair<int,int>& p){
                        area += (0.5*pi /180 * (p.second*p.second - p.first*p.first));
                    });
                }
            }
        );
        
        cout<<fixed<<setprecision(8)<<area<<endl;

    }
}