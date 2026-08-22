class Solution {
public:
    int hammingDistance(int x, int y) {
        int xorVal = x ^ y;
        int count = 0;
        while (xorVal) {
            count += (xorVal & 1); 
            xorVal >>= 1;   
        }
        return count;
    }
};