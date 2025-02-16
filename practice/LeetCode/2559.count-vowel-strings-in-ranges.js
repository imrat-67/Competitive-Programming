/*
 * @lc app=leetcode id=2559 lang=javascript
 *
 * [2559] Count Vowel Strings in Ranges
 */

// @lc code=start
/**
 * @param {string[]} words
 * @param {number[][]} queries
 * @return {number[]}
 */

function ck(s){
    let v = ['a','e','i','o','u'];
    return v.includes(s.at(0)) && v.includes(s.at(-1));
};

var vowelStrings = function(words, queries) {
    let n = words.length;
    let ar =new Array(n+1).fill(0);

    for(let i = 0; i<n; i++){
        ar[i+1] = ck(words[i]);
        ar[i+1] += ar[i];
    };
    
    let ans = new Array(queries.length);
    for(let i = 0; i<queries.length; i++) {
        let vc = queries[i];
        ans[i] = ar[vc[1]+1]-ar[vc[0]];
    }

    return ans;
};
// @lc code=end
