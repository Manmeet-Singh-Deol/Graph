class Solution {
public:
    int maxNumberOfFamilies(int n, vector<vector<int>>& reservedSeats) {
       unordered_map<int, unordered_set<int>> reserved;
    
    for (auto &seat : reservedSeats) {
        reserved[seat[0]].insert(seat[1]);
    }
    
    int result = 0;
    for (auto &row : reserved) {
        bool left = true, middle = true, right = true;
        
        for (int i = 2; i <= 5; i++) {
            if (row.second.count(i)) left = false;
        }
        for (int i = 6; i <= 9; i++) {
            if (row.second.count(i)) right = false;
        }
        for (int i = 4; i <= 7; i++) {
            if (row.second.count(i)) middle = false;
        }
        
        if (left && right) result += 2;
        else if (left || right || middle) result += 1;
    }
    result += (n - reserved.size()) * 2;
    
    return result; 
    }
};