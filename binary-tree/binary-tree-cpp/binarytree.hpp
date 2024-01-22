#include <vector>

namespace binary_tree {
using namespace std;

// 节点定义
struct Node {
    int val = -1;
    struct Node* left = nullptr;
    struct Node* right = nullptr;
    explicit Node(int val) : val(val) {}
    explicit Node(int val, Node* left) : val(val), left(left) {}
    explicit Node(int val, Node* left, Node* right)
        : val(val), left(left), right(right) {}
};

// 转化树为数组表示
vector<int> ToArray(Node* root);
// 转化数组为树表示
Node* FromArray(const vector<int>& a);

// 先序遍历/前序遍历 (递归)
void PreOrder(Node* root, vector<int>& ans);
// 中序遍历 (递归)
void InOrder(Node* root, vector<int>& ans);
// 后序遍历 (递归)
void PostOrder(Node* root, vector<int>& ans);

// 先序遍历/前序遍历 (非递归)
vector<int> PreOrder(Node* root);
// 中序遍历 (非递归)
vector<int> InOrder(Node* root);
// 后序遍历 (递归)
vector<int> PostOrder(Node* root);

// BFS
vector<int> BFS(Node* root);

// 层序遍历
vector<vector<int>> LevelOrder(Node* root);

}  // namespace binary_tree
