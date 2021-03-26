// 链表类问题

#include <assert.h>   // for assert
#include <stdbool.h>  // for bool
#include <stdio.h>    // for printf

// 单链表
struct Node {
    int v;  // 数据
    struct Node *next;
};

// 打印链表
void Print(struct Node *node) {
    while (node != NULL) {
        printf("%d ", node->v);
        node = node->next;
    }
    printf("\n");
}

// 插入一个结点 a 到结点 b 之前
// 如果找不到 b 则不插入，返回 false
bool Insert(struct Node *node, struct Node *a, struct Node *b) {
    struct Node *prev = NULL;
    while (node != NULL) {
        if (node == b) {
            // 插入
            if (prev != NULL) prev->next = a;
            if (a != NULL) a->next = b;
            return true;
        }
        prev = node;
        node = node->next;
    }
    return false;
}

// 删除一个结点 a
// 返回是否删除成功, 找不到返回 false
bool Remove(struct Node *node, struct Node *a) {
    struct Node *prev = NULL;
    while (node != NULL) {
        if (node == a) {
            // 删除
            if (prev != NULL) prev->next = node->next;
            return true;
        }
        prev = node;
        node = node->next;
    }
    return false;
}

// 反转链表，返回新的链表头
// https://leetcode-cn.com/problems/fan-zhuan-lian-biao-lcof/
struct Node *Reverse(struct Node *node) {
    struct Node *prev = NULL;
    while (node != NULL) {
        struct Node *next = node->next;
        node->next = prev;
        prev = node;
        node = next;
    }
    return prev;
}

// 获取链表长度
int Length(struct Node *node) {
    int i = 0;
    while (node != NULL) {
        node = node->next;
        i++;
    }
    return i;
}

// 获取链表的尾巴
struct Node *Tail(struct Node *node) {
    struct Node *prev = NULL;
    while (node != NULL) {
        prev = node;
        node = node->next;
    }
    return prev;
}

// 找出链表中间的节点
// abcd => b
// abcde => c
struct Node *Middle(struct Node *node) {
    struct Node *slow = node;  // 一次走一步
    struct Node *fast = node;  // 一次走两步
    struct Node *prev = NULL;  // 慢指针前的节点

    while (fast != NULL) {
        // 每人一步
        fast = fast->next;
        prev = slow;
        slow = slow->next;
        // fast 多走一步
        if (fast != NULL) fast = fast->next;
    }
    return prev;
}

// 判断回文链表，回文是指值回文
// 1. 入栈，出栈比较 ，空间 O(n)
// 2. 反转链表，比较 ，空间 O(n)
// 3. 找尾巴和中间节点，反转后半段，再比较 空间 O(1)
// 前两个比较容易，此处是第三种方法。
// https://leetcode-cn.com/problems/palindrome-linked-list-lcci/
bool IsPalindromic(struct Node *node) {
    struct Node *head = node;
    struct Node *mid = Middle(node);
    struct Node *tail = Reverse(mid);

    // 从头、尾对向比较
    struct Node *n1 = head, *n2 = tail;
    while (n1 != NULL && n2 != NULL) {
        // 奇数情况下：两边一样长
        // 偶数情况下，左边比右边短一位
        // 综合判断 n1 && n2 都非空，无碍
        if (n1->v == n2->v) {
            n1 = n1->next;
            n2 = n2->next;
        } else {
            return false;
        }
    }
    return true;
}

// 找出两个单链表的交叉点，没有交叉点则返回 NULL
// https://leetcode-cn.com/problems/liang-ge-lian-biao-de-di-yi-ge-gong-gong-jie-dian-lcof/
struct Node *Intersection(struct Node *a, struct Node *b) {
    struct Node *na = a;
    struct Node *nb = b;

    while (na != nb) {
        if (na != NULL)
            na = na->next;
        else
            na = b;

        if (nb != NULL)
            nb = nb->next;
        else
            nb = a;
    }
    return na;
}

// 判断单链表是否存在环
// https://leetcode-cn.com/problems/linked-list-cycle/
bool HasCycle(struct Node *node) {
    struct Node *slow = node;
    struct Node *fast = node;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next;
        fast = fast->next;
        if (slow == fast) return true;
    }
    return false;
}

// 如果单链表存在环，返回其入口节点
// https://leetcode-cn.com/problems/linked-list-cycle-ii/
struct Node *CycleEntry(struct Node *node) {
    // 找到相遇节点，同 HasCycle
    struct Node *slow = node;
    struct Node *fast = node;

    while (1) {
        if (fast == NULL || fast->next == NULL) return NULL;
        slow = slow->next;
        fast = fast->next;
        fast = fast->next;
        if (slow == fast) break;
    }

    // slow 是相遇节点, fast 重置到头，各自一步一步走
    fast = node;
    while (fast != NULL && slow != NULL) {
        if (slow == fast) return slow;
        slow = slow->next;
        fast = fast->next;
    }
    return NULL;
}

// 合并两个有序链表，返回新链表的头，要求原地 O(1)
// https://leetcode-cn.com/problems/merge-two-sorted-lists/
struct Node *MergeSortedList(struct Node *a, struct Node *b) {
    struct Node *c = NULL;
    struct Node *head = NULL;  // c's head
    struct Node *prev = NULL;  // c's prev

    // 合并
    while (a != NULL && b != NULL) {
        if (a->v <= b->v) {
            c = a;
            a = a->next;
        } else {
            c = b;
            b = b->next;
        }
        if (head == NULL) head = c;
        if (prev != NULL) prev->next = c;
        prev = c;
    }

    // 拷贝没有迭代完的链表
    while (a != NULL) {
        c = a;
        a = a->next;
        if (head == NULL) head = c;
        if (prev != NULL) prev->next = c;
        prev = c;
    }

    while (b != NULL) {
        c = b;
        b = b->next;
        if (head == NULL) head = c;
        if (prev != NULL) prev->next = c;
        prev = c;
    }
    return head;
}

// 链表排序，从小到大
// https://leetcode-cn.com/problems/sort-list/
// 采用归并排序
struct Node *Sort(struct Node *node) {
    // 递归终止
    if (node == NULL || node->next == NULL) return node;

    // 分割链表，找出中间的节点
    struct Node *mid = Middle(node);
    // 分割为左右两个链表
    struct Node *a = node;
    // 此时至少两个节点, mid 必然有后节点
    struct Node *b = mid->next;
    // 左边链表以 mid 结尾，封死其结尾
    mid->next = NULL;

    // 递归
    struct Node *a1 = Sort(a);
    struct Node *b1 = Sort(b);

    // 合并
    return MergeSortedList(a1, b1);
}

////////
// 测试
///////

void TestReverse() {
    struct Node c = {3, NULL};
    struct Node b = {2, &c};
    struct Node a = {1, &b};

    struct Node *d = Reverse(&a);

    assert(d == &c);
    assert(d->next == &b);
    assert(d->next->next == &a);
}

void TestInsert() {
    struct Node d = {4, NULL};
    struct Node c = {3, NULL};
    struct Node b = {2, &c};
    struct Node a = {1, &b};
    assert(Insert(&a, &d, &d) == false);
    assert(Insert(&a, &d, &b) == true);
    assert(a.next == &d);
    assert(a.next->next == &b);

    assert(Insert(&a, NULL, &d) == true);
    assert(a.next == NULL);
}

void TestRemove() {
    struct Node f = {6, NULL};
    struct Node e = {5, NULL};
    struct Node d = {4, &e};
    struct Node c = {3, &d};
    struct Node b = {2, &c};
    struct Node a = {1, &b};

    assert(Remove(&a, &f) == false);
    assert(Remove(&a, &c) == true);
    assert(a.next == &b);
    assert(a.next->next == &d);
    assert(a.next->next->next == &e);
}

void TestLength() {
    struct Node c = {3, NULL};
    struct Node b = {2, &c};
    struct Node a = {1, &b};
    assert(Length(&a) == 3);
}

void TestMiddle() {
    struct Node c = {3, NULL};
    struct Node b = {2, &c};
    struct Node a = {1, &b};
    assert(Middle(&a) == &b);

    struct Node d1 = {4, NULL};
    struct Node c1 = {3, &d1};
    struct Node b1 = {2, &c1};
    struct Node a1 = {1, &b1};
    assert(Middle(&a1) == &b1);
}

void TestTail() {
    struct Node c = {3, NULL};
    struct Node b = {2, &c};
    struct Node a = {1, &b};
    assert(Tail(&a) == &c);
}

void TestIsPalindromic() {
    struct Node d = {4, NULL};
    struct Node c = {3, &d};
    struct Node b = {2, &c};
    struct Node a = {1, &b};
    assert(!IsPalindromic(&a));

    struct Node e1 = {1, NULL};
    struct Node d1 = {2, &e1};
    struct Node c1 = {3, &d1};
    struct Node b1 = {2, &c1};
    struct Node a1 = {1, &b1};
    assert(IsPalindromic(&a1));
}

void TestIntersection() {
    struct Node f = {6, NULL};
    struct Node e = {5, &f};
    struct Node d = {4, &e};
    struct Node c = {3, &d};
    struct Node b = {2, &c};
    struct Node a = {1, &b};

    struct Node b1 = {4, &e};
    struct Node a1 = {3, &b1};

    assert(Intersection(&a, &a1) == &e);
}

void TestHasCycle() {
    struct Node f = {6, NULL};
    struct Node e = {5, &f};
    struct Node d = {4, &e};
    struct Node c = {3, &d};
    struct Node b = {2, &c};
    struct Node a = {1, &b};
    f.next = &d;
    assert(HasCycle(&a) == true);
}

void TestCycleEntry() {
    struct Node f = {6, NULL};
    struct Node e = {5, &f};
    struct Node d = {4, &e};
    struct Node c = {3, &d};
    struct Node b = {2, &c};
    struct Node a = {1, &b};
    f.next = &d;
    assert(CycleEntry(&a) == &d);
}

void TestMergeSortedList() {
    struct Node e = {8, NULL};
    struct Node d = {6, &e};
    struct Node c = {5, &d};
    struct Node b = {3, &c};
    struct Node a = {1, &b};

    struct Node c1 = {7, NULL};
    struct Node b1 = {2, &c1};
    struct Node a1 = {1, &b1};

    struct Node *h = MergeSortedList(&a, &a1);

    assert(h == &a);
    assert(h->next == &a1);
    assert(h->next->next == &b1);
    assert(h->next->next->next == &b);
    assert(h->next->next->next->next == &c);
    assert(h->next->next->next->next->next == &d);
    assert(h->next->next->next->next->next->next == &c1);
    assert(h->next->next->next->next->next->next->next == &e);
    assert(h->next->next->next->next->next->next->next->next == NULL);
}

void TestSort() {
    struct Node f = {4, NULL};
    struct Node e = {3, &f};
    struct Node d = {1, &e};
    struct Node c = {2, &d};
    struct Node b = {5, &c};
    struct Node a = {6, &b};

    struct Node *h = Sort(&a);
    assert(h == &d);
    assert(h->next == &c);
    assert(h->next->next == &e);
    assert(h->next->next->next == &f);
    assert(h->next->next->next->next == &b);
    assert(h->next->next->next->next->next == &a);
}

int main(void) {
    TestReverse();
    TestInsert();
    TestRemove();
    TestLength();
    TestTail();
    TestMiddle();
    TestIsPalindromic();
    TestIntersection();
    TestHasCycle();
    TestCycleEntry();
    TestMergeSortedList();
    TestSort();
    return 0;
}
