struct Node {
    char leftChar, rightChar;
    int leftLen, rightLen, maxLen, len;
    Node(char c='?', int l=0) {
        leftChar = rightChar = c;
        leftLen = rightLen = maxLen = (l ? 1 : 0);
        len = l;
    }
};

class SegmentTree {
    int n;
    string s;
    vector<Node> tree;

    Node merge(Node a, Node b) {
        Node res;
        res.leftChar = a.leftChar;
        res.rightChar = b.rightChar;
        res.len = a.len + b.len;

        // leftLen: extend if entire left segment is uniform
        res.leftLen = a.leftLen;
        if (a.leftLen == a.len && a.leftChar == b.leftChar) {
            res.leftLen = a.len + b.leftLen;
        }

        // rightLen: extend if entire right segment is uniform
        res.rightLen = b.rightLen;
        if (b.rightLen == b.len && b.rightChar == a.rightChar) {
            res.rightLen = b.len + a.rightLen;
        }

        // maxLen: best of left, right, or crossing boundary
        res.maxLen = max({a.maxLen, b.maxLen,
                          (a.rightChar == b.leftChar ? a.rightLen + b.leftLen : 0)});
        return res;
    }

    void build(int idx, int l, int r) {
        if (l == r) {
            tree[idx] = Node(s[l], 1);
            return;
        }
        int mid = (l + r) / 2;
        build(idx*2, l, mid);
        build(idx*2+1, mid+1, r);
        tree[idx] = merge(tree[idx*2], tree[idx*2+1]);
    }

    void update(int idx, int l, int r, int pos, char c) {
        if (l == r) {
            tree[idx] = Node(c, 1);
            return;
        }
        int mid = (l + r) / 2;
        if (pos <= mid) update(idx*2, l, mid, pos, c);
        else update(idx*2+1, mid+1, r, pos, c);
        tree[idx] = merge(tree[idx*2], tree[idx*2+1]);
    }

public:
    SegmentTree(string str) {
        s = str;
        n = s.size();
        tree.resize(4*n);
        build(1, 0, n-1);
    }

    void update(int pos, char c) {
        update(1, 0, n-1, pos, c);
    }

    int getMax() {
        return tree[1].maxLen;
    }
};

class Solution {
public:
    vector<int> longestRepeating(string s, string queryCharacters, vector<int>& queryIndices) {
        SegmentTree st(s);
        vector<int> ans;
        for (int i = 0; i < queryCharacters.size(); i++) {
            st.update(queryIndices[i], queryCharacters[i]);
            ans.push_back(st.getMax());
        }
        return ans;
    }
};
