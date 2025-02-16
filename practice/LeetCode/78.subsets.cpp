/*
 * @lc app=leetcode id=78 lang=cpp
 *
 * [78] Subsets
 */

// @lc code=start
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> ans;
        vector<int> vc;
        for(int i=0; i<(1<<nums.size()); i++){
            for(int j=0; j<nums.size(); j++){
                if(i&(1<<j)) vc.push_back(nums[j]); 
            }
            ans.push_back(vc);
            vc.clear();
        }
        return ans;
    }
};
// @lc code=end

