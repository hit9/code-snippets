#include <vector>
using namespace std;
// Definition for a Node.
class Node {
   public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) { val = _val; }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};

class Solution {
   public:
    vector<int> preorder(Node* root) {
        vector<int> ans;
        dfs(root, ans);
        return ans;
    }
    void dfs(Node* root, vector<int>& ans) {
        if (root == nullptr) return;
        ans.push_back(root->val);
        for (auto ch : root->children) dfs(ch, ans);
    }
};
