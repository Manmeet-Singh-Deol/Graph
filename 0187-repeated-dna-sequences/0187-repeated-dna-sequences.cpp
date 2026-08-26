class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        unordered_map<string, int> freq;
        vector<string> result;
        int n = s.size();
        
        for (int i = 0; i + 10 <= n; i++) {
            string sub = s.substr(i, 10);
            freq[sub]++;
            if (freq[sub] == 2) { 
                result.push_back(sub);
            }
        }
        return result;
    }
};
