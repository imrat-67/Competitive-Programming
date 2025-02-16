<?php
/*
 * @lc app=leetcode id=2270 lang=php
 *
 * [2270] Number of Ways to Split Array
 */

// @lc code=start
class Solution {

    /**
     * @param Integer[] $nums
     * @return Integer
     */
    function waysToSplitArray($nums) {
        $array = array_fill(0,sizeof($nums)+1,0);
        for($i=0; $i<sizeof($nums); $i++){
            $array[$i+1] += $nums[$i] + $array[$i];   
        }
        
        $sum = array_sum($nums);

        $cnt = 0;
        for($i=0; $i<sizeof($nums)-1; $i++){
            if($array[$i+1]>=($sum-$array[$i+1])) $cnt++;
        }

        return $cnt;
    }
}
// @lc code=end

$input = trim(fgets(STDIN));
$input = trim(fgets(STDIN));
$input = explode(' ',$input);

$var = new Solution();

echo $var->waysToSplitArray($input)."\n";

?>