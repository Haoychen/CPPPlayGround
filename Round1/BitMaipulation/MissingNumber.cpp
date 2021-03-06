/*
 * Given an array containing n distinct numbers taken from 0, 1, 2, ..., n, 
 * find the one that is missing from the array.
 * For example,
 * Given nums = [0, 1, 3] return 2.
 */

class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int res = 0;
        for (int i = 0; i < nums.size() + 1; ++i) {
            res ^= i;
        }

        for (const auto &num: nums) {
            res ^= num;
        }

        return res;
    }
};
