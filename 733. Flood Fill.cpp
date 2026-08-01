class Solution {
public:
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color) {
        int original = image[sr][sc];
        if (original == color) return image; // no change needed
        dfs(image, sr, sc, original, color);
        return image;
    }
    
    void dfs(vector<vector<int>>& image, int r, int c, int original, int color) {
        // boundary + color check
        if (r < 0 || c < 0 || r >= image.size() || c >= image[0].size() || image[r][c] != original)
            return;
        
        image[r][c] = color; // recolor
        
        // explore 4 directions
        dfs(image, r+1, c, original, color);
        dfs(image, r-1, c, original, color);
        dfs(image, r, c+1, original, color);
        dfs(image, r, c-1, original, color);
    }
};
