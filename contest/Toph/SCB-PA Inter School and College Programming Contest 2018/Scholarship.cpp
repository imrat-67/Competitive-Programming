#include<bits/stdc++.h>
using namespace std;

int main(){
    string s; 
    vector<int> vc;
    int n,bd;

    getline(cin,s);
    stringstream ss(s);
    while(ss>>n) vc.push_back(n); n = vc.size();
    cin>>bd;

    sort(vc.begin(),vc.end());
    double v = bd*1.0/n;

    for(int i=1; i<=n; i++){
        if(vc[i-1]>=v) break;
        bd -= vc[i-1];
        v = bd*1.0/(n-i);
    }

    cout<<fixed<<setprecision(2)<<v<<endl;
}

/* -------Binary Search Solution---------

#include<bits/stdc++.h>
using namespace std;

bool ck(double mid,vector<int>& vc,int tt){
    double sum = 0;
    for(auto& i: vc) sum += min(static_cast<double>(i),mid);
    return sum >= tt;
}

int main(){
    string s;
    getline(cin,s);
    stringstream ss(s);
    vector<int> vc;
    int n;
    while(ss>>n) vc.push_back(n);

    double lo,hi,v=100,tt; lo=0; cin>>tt; hi = tt;
    while(lo<hi and v-->0){
        double mid = (lo+hi)/2;
        if(ck(mid,vc,tt)) hi = mid;
        else lo = mid+0.005;
    }

    cout<<fixed<<setprecision(2)<<hi<<endl;
}

*/