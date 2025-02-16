#include<bits/stdc++.h>>
using namespace std;

class Solution {
public:
    double maxAmount(string initialCurrency, vector<vector<string>>& pairs1, vector<double>& rates1, 
    vector<vector<string>>& pairs2, vector<double>& rates2) {

        set<pair<string,double>> st;
        st.insert(make_pair(initialCurrency,1));

        for(auto &dfdf: pairs1)
        for(int i=0; i<pairs1.size(); i++){
            for(auto &x: st){
                if(x.first==pairs1[i][0]) st.insert(make_pair(pairs1[i][1],x.second*rates1[i]));
                else if(x.first==pairs1[i][1]) st.insert(make_pair(pairs1[i][0],x.second/rates1[i]));
            }
        }

        for(auto &dfdf: pairs2)
        for(int i=0; i<pairs2.size(); i++){
            for(auto &x: st){
                if(x.first==pairs2[i][0]) st.insert(make_pair(pairs2[i][1],x.second*rates2[i]));
                else if(x.first==pairs2[i][1]) st.insert(make_pair(pairs2[i][0],x.second/rates2[i]));
            }
        }

        double mx = 0;
        for(auto &x: st) if(x.first==initialCurrency) mx = max(mx,x.second);    

        return mx;    
    }
};