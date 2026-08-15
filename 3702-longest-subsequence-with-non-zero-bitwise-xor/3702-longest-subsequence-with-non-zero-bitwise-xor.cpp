class Solution {
public:
    int longestSubsequence(vector<int>& nums) {
        int n = nums.size();
        int xor_all = 0;
        for (int x : nums) xor_all ^= x;

        if (xor_all != 0) return n;          // Case 1
        bool allZero = true;
        for (int x : nums) if (x != 0) allZero = false;

        if (allZero) return 0;               // Case 2a
        return n - 1; 
    }
};