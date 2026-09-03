class Solution {
public:
    bool uniformArray(vector<int>& nums1) {
        int n = nums1.size();
        int minOdd = INT_MAX, minEven = INT_MAX;
        bool hasOdd = false, hasEven = false;
        for (int x : nums1) {
            if (x % 2 == 0) {
                hasEven = true;
                minEven = min(minEven, x);
            } else {
                hasOdd = true;
                minOdd = min(minOdd, x);
            }
        }
        if (!hasOdd || !hasEven) return true;
        bool allOdd = true;
        for (int x : nums1) {
            if (x % 2 == 0) {
                if (x - minOdd < 1 || (x - minOdd) % 2 == 0) {
                    allOdd = false;
                    break;
                }
            }
        }
        bool allEven = true;
        for (int x : nums1) {
            if (x % 2 == 1) {
                if (x - minEven < 1 || (x - minEven) % 2 == 1) {
                    allEven = false;
                    break;
                }
            }
        }

        return allOdd || allEven;
    }
};
