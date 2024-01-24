#include <iostream>
#include <queue>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
   public:
    int minimumOperations(vector<int>& nums, int start, int goal) {
        queue<int> q1, q2;

        // 去重表
        unordered_set<int> st1;
        unordered_set<int> st2;

        pushq(q1, start, st1);
        pushq(q2, goal, st2);

        int steps = 0;

        // 两个队列任一个空时, 就是没找到
        while (!q1.empty() && !q2.empty()) {
            // 确保 q1 更小的队列
            if (q1.size() > q2.size()) swap(q1, q2), swap(st1, st2);
            // 每一次扩展小的队列
            steps++;
            if (extend(q1, nums, st1, st2)) return steps;
        }

        return -1;
    }

    // 扩展给定的队列, st 是自己的去重表, st2 是对方的
    // 发现重叠时, 返回 true
    bool extend(queue<int>& q, const vector<int>& nums, unordered_set<int>& st,
                const unordered_set<int>& st2) {
        int n = q.size();
        while (n--) {
            auto x = q.front();
            q.pop();

            for (auto y : nums) {
                int z1 = x + y, z2 = x - y, z3 = x ^ y;

                // 判定是否和对方搜索范围出现重叠
                if (st2.find(z1) != st2.end()) return true;
                if (st2.find(z2) != st2.end()) return true;
                if (st2.find(z3) != st2.end()) return true;

                // 超过限制的, 只可以进行一次计算, 不再入队
                if (0 <= z1 && z1 <= 1000) pushq(q, z1, st);
                if (0 <= z2 && z2 <= 1000) pushq(q, z2, st);
                if (0 <= z3 && z3 <= 1000) pushq(q, z3, st);
            }
        }
        return false;
    }

    inline void pushq(queue<int>& q, int z, unordered_set<int>& st) {
        if (st.find(z) != st.end()) return;  // 去重
        st.insert(z);
        q.push(z);
    }
};

int main(void) {
    vector<int> nums{3, 5, 7};
    int start = 0, goal = -4;
    Solution s;
    cout << s.minimumOperations(nums, start, goal) << endl;
    return 0;
}
