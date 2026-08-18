class Solution {
public:
    int largestInteger(vector<int>& nums, int k) {
        int n = nums.size();
        unordered_map<int,int> freq;
        for (int x : nums) freq[x]++;

        // Case 1: k == 1
        if (k == 1) {
            int ans = -1;
            for (auto &p : freq) {
                if (p.second == 1) ans = max(ans, p.first);
            }
            return ans;
        }

        // Case 2: k == n
        if (k == n) {
            return *max_element(nums.begin(), nums.end());
        }

        // Case 3: 1 < k < n
        int left = nums[0], right = nums[n-1];
        bool leftValid = (freq[left] == 1);
        bool rightValid = (freq[right] == 1);

        if (leftValid && rightValid) return max(left, right);
        if (leftValid) return left;
        if (rightValid) return right;
        return -1;
    }
};
