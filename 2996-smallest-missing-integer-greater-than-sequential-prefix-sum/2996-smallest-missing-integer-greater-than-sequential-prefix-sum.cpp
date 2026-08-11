class Solution {
public:
    int missingInteger(vector<int>& nums) {
        int i=0;
        while(i+1<nums.size()&& nums[i+1]==nums[i]+1){
            i++;
        }
        int ps=0;
        for(int j=0;j<=i;j++){
            ps+=nums[j];
        }
        unordered_set<int> st(nums.begin(), nums.end());
        int  x=ps;
        while(st.count(x)){
            x++;
        }
        return x;
    }
};