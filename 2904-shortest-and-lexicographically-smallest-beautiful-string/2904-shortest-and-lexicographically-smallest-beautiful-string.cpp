class Solution {
public:
    string shortestBeautifulSubstring(string s, int k) {
        int n = s.size();
        int left = 0, ones = 0;
        int minLen = INT_MAX;
        string best = "";

        for (int right = 0; right < n; right++) {
            if (s[right] == '1') ones++;
            while (ones >= k) {
                if (ones == k) {
                    int len = right - left + 1;
                    string candidate = s.substr(left, len);

                    if (len < minLen || (len == minLen && candidate < best)) {
                        minLen = len;
                        best = candidate;
                    }
                }
                if (s[left] == '1') ones--;
                left++;
            }
        }
        return best;
    }
};
