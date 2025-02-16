#include<bits/stdc++.h>
using namespace std;

int main(){
    int t; cin>>t;
        while(t--){
        int n,m; cin>>n>>m;
        string s1,s2;
        list<int> li(m);

        cin>>s1;
        for(auto& i: li) cin>>i;
        cin>>s2;

        li.sort();
        sort(s2.begin(),s2.end());
        li.resize(distance(li.begin(),unique(li.begin(),li.end())));

        int j = 0;
        for(auto i: li){
            s1[i-1] = s2[j];
            j++;
        }

        cout<<s1<<endl;
    }
}