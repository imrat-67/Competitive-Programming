/*
 * @lc app=leetcode id=1 lang=cpp
 *
 * [1] Two Sum
 */

// @lc code=start
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        
        vector<pair<int,int>> vc;
        
        for(int i=0; i<nums.size(); i++){
            vc.push_back(make_pair(nums[i],i));
        }

        sort(vc.begin(),vc.end());

        int i=0,j=nums.size()-1;

        while(i<j){
            if(vc[i].first+vc[j].first==target) return {vc[i].second,vc[j].second};
            if(vc[i].first+vc[j].first>target) j--;
            else i++;
        }
        return {-1};
    }
};
// @lc code=end

