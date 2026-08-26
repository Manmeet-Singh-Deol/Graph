class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        long xorAll = 0;
        for (int x : nums) xorAll ^= x;

        long diffBit = xorAll & -xorAll;

        int a = 0, b = 0;
        for (int x : nums) {
            if (x & diffBit) a ^= x;
            else b ^= x;
        }
        return {a, b};
    }
};
