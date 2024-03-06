#include <vector>

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
   public:
    // 翻转 [start, end)
    ListNode* reverse(ListNode* start, const ListNode* end) {
        ListNode vhead;  // 虚拟头
        ListNode* next = nullptr;
        for (ListNode* x = start; x != end; x = next) {
            next = x->next;
            x->next = vhead.next;
            vhead.next = x;
        }
        return vhead.next;
    }
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode vhead(0, head);  // 虚拟头
        // x 是主迭代指针, p 是 x 的前驱
        ListNode *x = head, *p = &vhead;
        while (x) {
            // 备份一下本次翻转的起点, 翻转后会成为尾部
            auto y = x;
            // 前进 k 个, 翻转一次, 或者到 null
            int j = k;
            p->next = x;  // 暂时先指向本次翻转的起点
            for (; x && j; x = x->next) j--;
            if (!x && j != 0) break;  // 剩余的不变
            p->next = reverse(y, x);
            // 原来的起点翻转后成为下一次的前驱
            p = y;
        }
        return vhead.next;
    }
};
