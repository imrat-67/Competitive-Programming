#include<bits/stdc++.h>>
using namespace std;

class Solution {
public:
    int buttonWithLongestTime(vector<vector<int>>& events) {
        map<int,set<int>> mp;
        int pv = 0;
        for(auto &i: events){
            mp[i[1]-pv].insert(i[0]);
            pv = i[1];
        }

        auto it = --mp.end(); 
        return *(it->second.begin()); 
    }
};