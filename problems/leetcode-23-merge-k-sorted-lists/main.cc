// https://leetcode.cn/problems/merge-k-sorted-lists
// 23. 合并 K 个升序链表
//
// 给你一个链表数组，每个链表都已经按升序排列。
// 请你将所有链表合并到一个升序链表中，返回合并后的链表。

#include <vector>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
   public:
    ListNode* MergeTwoLists(ListNode* a, ListNode* b) {
        ListNode head;  // 虚拟头节点，栈上，自动回收
        auto node = &head;

        while (a != nullptr && b != nullptr) {
            if (a->val <= b->val) {
                node->next = a;
                a = a->next;
            } else {
                node->next = b;
                b = b->next;
            }
            node = node->next;
        }

        if (a != nullptr) node->next = a;
        if (b != nullptr) node->next = b;

        return head.next;  // 返回真实头节点
    }

    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if (lists.size() == 0) return nullptr;
        if (lists.size() == 1) return lists[0];
        if (lists.size() == 2) return MergeTwoLists(lists[0], lists[1]);

        // 二分数组, 两两合并
        int n = lists.size();

        vector<ListNode*> L;
        for (int i = 0; i < (n + 1) / 2; i++) L.push_back(lists[i]);

        vector<ListNode*> R;
        for (int i = L.size(); i < n; i++) R.push_back(lists[i]);

        return MergeTwoLists(mergeKLists(L), mergeKLists(R));
    }
};
