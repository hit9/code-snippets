#include <iostream>
#include <string_view>

// 字符集大小
const int C = 26;
const int MAX_N = 10010;

// 静态字典树
class Trie {
   private:
    int n = 0;
    // tree[i] 表示第 i 个节点,
    // tree[i][ch] -> j 表示字母 ch 的孩子指向第 j 个节点
    int tree[MAX_N][C];
    // end[i] 表示第 i 个节点是否是某个单词的末尾
    bool end[MAX_N];

   public:
    explicit Trie() : n(0) {
        memset(tree, 0, MAX_N * C);
        memset(end, false, MAX_N);
    };

    // 添加一个元素
    void put(std::string_view s) {
        // 尝试找到一个没有用过的节点 j
        int j = 0;
        for (auto ch : s) {
            int k = ch - 'a';
            // 已用的节点自增，指向下一个节点
            if (tree[j][k] == 0) tree[j][k] = ++n;
            j = tree[j][k];
        }
        end[j] = true;
    }

    // 查找一个单词是否在其中，返回节点索引
    bool find(std::string_view s) {
        int j = 0;
        for (auto ch : s) {
            int k = ch - 'a';
            if (tree[k][k] == 0) return false;
            j = tree[j][k];
        }
        return end[j];
    }

    // 返回节点数目
    int size() { return n; }
};

int main(void) {
    Trie t;
    t.put("abcdefg");
    t.put("abcdehg");
    std::cout << t.find("abcdefg") << std::endl;
    return 0;
}
