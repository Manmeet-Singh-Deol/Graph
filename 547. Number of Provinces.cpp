class Solution {
private:
    void dfs(int node, vector<int> adjls[], vector<int>& vis) {
        vis[node] = 1;
        for (auto it : adjls[node]) {
            if (!vis[it]) {
                dfs(it, adjls, vis);
            }
        }
    }

public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        int l = isConnected.size();
        vector<int> adjls[l];
        for (int i = 0; i < l; i++) {
            for (int j = 0; j < l; j++) {
                if (isConnected[i][j] == 1 && i != j) {
                    adjls[i].push_back(j);
                    adjls[j].push_back(i);
                }
            }
        }
        vector<int> vis(l, 0);
        int cnt = 0;
        for (int i = 0; i < l; i++) {
            if (!vis[i]) {
                cnt++;
                dfs(i, adjls, vis);
            }
        }
        return cnt;
    }
};
