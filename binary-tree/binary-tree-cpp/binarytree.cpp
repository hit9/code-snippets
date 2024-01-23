#include "binarytree.hpp"

#include <queue>
#include <stack>
#include <utility>

namespace binary_tree {

// 转化树为数组表示
vector<int> ToArray(Node* root) {
    vector<int> ans;
    queue<Node*> q;
    q.push(root);

    // 记录自上一个非空节点以后的空节点数量
    int ec = 0;

    while (!q.empty()) {
        auto node = q.front();
        q.pop();
        if (node == nullptr) {
            ec++;
            continue;
        } else {
            // 把前面的空节点放进来
            // 为了防止数据末尾有 -1，所以遇到非空节点时才把-1刷出来
            for (int i = 0; i < ec; i++) ans.push_back(-1);
            ec = 0;
            // 添加当前非空节点的数据
            ans.push_back(node->val);
            // 添加下一层节点到队列
            q.push(node->left);
            q.push(node->right);
        }
    }
    return ans;
}

// 转化数组为树表示 (ToArray 的逆函数)
Node* FromArray(const vector<int>& a) {
    if (a.empty()) return nullptr;
    int n = a.size();

    // q 记录上一层节点
    queue<Node*> q;
    auto root = new Node(a[0]);
    q.push(root);

    // 当前的迭代指针 i  和 数值 val
    int i = 1, val;

    while (!q.empty()) {
        auto node = q.front();
        q.pop();
        // 新建左孩子节点
        if (i < n) {
            val = a[i++];
            if (val != -1) node->left = new Node(val);
        }
        // 新建右孩子节点
        if (i < n) {
            val = a[i++];
            if (val != -1) node->right = new Node(val);
        }
        // 处理下一层
        if (node->left != nullptr) q.push(node->left);
        if (node->right != nullptr) q.push(node->right);
    }
    return root;
}

// 先序遍历/前序遍历 (递归)
void PreOrder(Node* root, vector<int>& ans) {
    if (root == nullptr) return;
    ans.push_back(root->val);
    PreOrder(root->left, ans);
    PreOrder(root->right, ans);
}

// 中序遍历 (递归)
void InOrder(Node* root, vector<int>& ans) {
    if (root == nullptr) return;
    InOrder(root->left, ans);
    ans.push_back(root->val);
    InOrder(root->right, ans);
}

// 后序遍历 (递归)
void PostOrder(Node* root, vector<int>& ans) {
    if (root == nullptr) return;
    PostOrder(root->left, ans);
    PostOrder(root->right, ans);
    ans.push_back(root->val);
}

// 先序遍历/前序遍历 (非递归)
vector<int> PreOrder(Node* root) {
    if (root == nullptr) return {};
    vector<int> ans;
    stack<pair<Node*, bool>> s;
    s.push({root, false});

    while (!s.empty()) {
        auto [node, visited] = s.top();
        s.pop();
        if (node == nullptr) continue;
        if (!visited) {
            // 最后再访问孩子
            s.push({node->right, false});
            s.push({node->left, false});
            // 先处理父节点
            s.push({node, true});
        } else {
            // 第二次访问时执行处理
            ans.push_back(node->val);
        }
    }
    return ans;
}

// 中序遍历 (非递归)
vector<int> InOrder(Node* root) {
    if (root == nullptr) return {};
    vector<int> ans;
    stack<pair<Node*, bool>> s;
    s.push({root, false});

    while (!s.empty()) {
        auto [node, visited] = s.top();
        s.pop();
        if (node == nullptr) continue;
        if (!visited) {
            // 最后访问右孩子
            s.push({node->right, false});
            // 再处理父节点
            s.push({node, true});
            // 先访问左孩子
            s.push({node->left, false});
        } else {
            // 第二次访问时执行处理
            ans.push_back(node->val);
        }
    }
    return ans;
}

// 后序遍历 (非递归)
vector<int> PostOrder(Node* root) {
    if (root == nullptr) return {};
    vector<int> ans;
    stack<pair<Node*, bool>> s;
    s.push({root, false});

    while (!s.empty()) {
        auto [node, visited] = s.top();
        s.pop();
        if (node == nullptr) continue;
        if (!visited) {
            // 最后处理父节点
            s.push({node, true});
            // 再访问右孩子
            s.push({node->right, false});
            // 先访问左孩子
            s.push({node->left, false});
        } else {
            // 第二次访问时执行处理
            ans.push_back(node->val);
        }
    }
    return ans;
}

// BFS
vector<int> BFS(Node* root) {
    vector<int> ans;
    queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        auto node = q.front();
        q.pop();
        if (node == nullptr) continue;
        ans.push_back(node->val);
        // 处理下一层
        q.push(node->left);
        q.push(node->right);
    }
    return ans;
}

// 层序遍历
vector<vector<int>> LevelOrder(Node* root) {
    if (root == nullptr) return {{}};

    vector<vector<int>> ans;
    ans.push_back({});

    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        int n = q.size();
        while (n--) {
            auto node = q.front();
            q.pop();

            if (node == nullptr) continue;

            ans.back().push_back(node->val);

            // 处理下一层
            if (node->left != nullptr) q.push(node->left);
            if (node->right != nullptr) q.push(node->right);
        }
        if (!q.empty()) ans.push_back({});
    }
    return ans;
}

}  // namespace binary_tree
