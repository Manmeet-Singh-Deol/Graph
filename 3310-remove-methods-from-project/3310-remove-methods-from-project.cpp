class Solution {
public:
    vector<int> remainingMethods(int n, int k, vector<vector<int>>& invocations) {
        vector<vector<int>> graph(n);
        for(auto &edge:invocations){
            graph[edge[0]].push_back(edge[1]);
        }

        vector<bool> suspicious(n, false);
        stack<int> st;
        st.push(k);
        suspicious[k] = true;
        while (!st.empty()) {
            int node = st.top(); st.pop();
            for (int nei : graph[node]) {
                if (!suspicious[nei]) {
                    suspicious[nei] = true;
                    st.push(nei);
                }
            }
        }
        for (auto &edge : invocations) {
            int a = edge[0], b = edge[1];
            if (!suspicious[a] && suspicious[b]) {
                vector<int> all(n);
                iota(all.begin(), all.end(), 0);
                return all;
            }
        }
        vector<int> result;
        for (int i = 0; i < n; i++) {
            if (!suspicious[i]) result.push_back(i);
        }
        return result;
    }
};