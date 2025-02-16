
/*
 * @lc app=leetcode id=1930 lang=java
 *
 * [1930] Unique Length-3 Palindromic Subsequences
 */

// @lc code=start

import java.util.LinkedHashSet;
import java.util.Set;

interface lamda{
    int func(int[][] ar,int pos,int n);
}

class Solution {
    public int countPalindromicSubsequence(String s) {

        int[][] ar = new int[26][s.length()+1];
        Set<Character> st = new LinkedHashSet<>();

        for(int i=0; i<s.length(); i++){
            st.add(s.charAt(i));
            int v = s.charAt(i) - 'a';
            ar[v][i+1] = 1;
            
            for(int j=0; j<26; j++) ar[j][i+1] += ar[j][i];
        }   
        
        lamda l = (arr,p,n) -> {
            int ft=0,ls=0;
            for(int i=0; i<=n; i++) if(arr[p][i] != 0) { ft = i; break; }
            for(int i=n; i>0; i--) if(arr[p][i]>arr[p][i-1]) { ls = i; break; }
            
            if(ft>=ls) return 0;
            int cnt = 0;
            for(int i=0; i<26; i++)
                if(arr[i][ls-1]-arr[i][ft]>0) cnt++;
           
            return cnt;
        };
        
        int ans = 0;
        for(Character c: st) ans += l.func(ar,c-'a',s.length());
        
        return ans;
    }
}
// @lc code=end

