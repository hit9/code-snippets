
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

const int N = 1e5 + 1;

struct UF {
    int fa[N], sz[N];  // 父节点数组, 集合大小
    int tot = 0;       // 节点标号指针
    int max_size = 1;

    int find(int x) {
        if (x == fa[x]) return x;
        return fa[x] = find(fa[x]);
    }

    void merge(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return;
        if (sz[a] > sz[b]) {
            fa[b] = a;
            sz[a] += sz[b];
            max_size = max(sz[a], max_size);
        } else {
            fa[a] = b;
            sz[b] += sz[a];
            max_size = max(sz[b], max_size);
        }
    }

    int add() {
        ++tot;
        fa[tot] = tot;
        sz[tot] = 1;
        return tot;
    }
};

class Solution {
   public:
    int longestConsecutive(vector<int>& nums) {
        if (nums.empty()) return 0;

        unordered_map<int, int> m;
        UF u;

        for (auto x : nums) {
            if (m[x]) continue;

            // m[x] 记录值为 x 的节点号
            m[x] = u.add();

            // 合并相邻的节点的集合
            if (m[x - 1]) u.merge(m[x], m[x - 1]);
            if (m[x + 1]) u.merge(m[x], m[x + 1]);
        }
        // 答案就是最大集合的大小
        return u.max_size;
    }
};

int main(void) {
    Solution s;
    vector<int> nums{0};
    cout << s.longestConsecutive(nums) << endl;
    return 0;
}
