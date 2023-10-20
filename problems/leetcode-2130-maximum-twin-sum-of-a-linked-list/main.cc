//https://leetcode.cn/problems/maximum-twin-sum-of-a-linked-list/description/
#include <iostream>
#include <stack>

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

using namespace std;

class Solution {
   public:
    int pairSum(ListNode *head) {
        int ans = 0;

        // 快指针 a 一次2步, 慢指针 b 一次1步
        auto a = head;
        auto b = head;

        // 记录左半部分的数字
        stack<int> s;

        while (a != nullptr) {
            a = a->next;
            if (a == nullptr) break;
            a = a->next;
            s.push(b->val);
            b = b->next;
        }

        // 出栈计算
        while (b != nullptr) {
            auto m = s.top() + b->val;
            s.pop();
            if (m > ans) ans = m;
            b = b->next;
        }

        return ans;
    }
};

int main(void) {
    ListNode d{1, nullptr};
    ListNode c{2, &d};
    ListNode b{4, &c};
    ListNode a{5, &b};

    Solution solution;
    cout << solution.pairSum(&a) << endl;
}
