struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
   public:
    ListNode* add(ListNode* l1, ListNode* l2, int k) {
        if (l1 == nullptr && l2 == nullptr && k == 0) return nullptr;

        int a = l1 == nullptr ? 0 : l1->val;
        int b = l2 == nullptr ? 0 : l2->val;

        int c = a + b + k;

        return new ListNode(c % 10,
                            add(l1 == nullptr ? nullptr : l1->next,
                                l2 == nullptr ? nullptr : l2->next, c / 10));
    }
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        return add(l1, l2, 0);
    }
};
