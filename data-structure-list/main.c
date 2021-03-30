// 链表类问题
// https://writings.sh/post/data-structure-list-common-algorithm-problems

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
    struct Node *head = &(struct Node){0, NULL};  // 虚拟头节点
    struct Node *prev = head;                     // c 的前驱节点
    struct Node *c = NULL;

    // 合并
    while (a != NULL && b != NULL) {
        if (a->v <= b->v) {
            c = a;
            a = a->next;
        } else {
            c = b;
            b = b->next;
        }
        prev->next = c;
        prev = c;
    }

    // 至多还有一个没有迭代完的链表
    if (a != NULL) prev->next = a;
    if (b != NULL) prev->next = b;

    return head->next;
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

// 链表分割
// https://leetcode-cn.com/problems/partition-list/
// 使得小于给定值的在左边，大于等于的在右边
// 要求保序。
// 两种思路：
// 1. 起两个链表头，小的、大的依次拣过去，最后拼接。
// 2. 加一个左哨兵，快慢指针，把遇到的小的追加到左边。
// 这里是第一种方法
struct Node *Partition(struct Node *head, int k) {
    struct Node *left_head = &(struct Node){0, NULL};
    struct Node *right_head = &(struct Node){0, NULL};

    struct Node *node = head;         // 迭代原链表
    struct Node *left = left_head;    // 迭代左链表
    struct Node *right = right_head;  // 迭代右链表

    while (node != NULL) {
        if (node->v < k) {
            // 拣到左边链表
            left->next = node;
            left = left->next;
        } else {
            // 拣到右边链表
            right->next = node;
            right = right->next;
        }
        node = node->next;
    }
    // 末尾抹 NULL
    right->next = NULL;
    // 拼接，并丢弃 right_head
    left->next = right_head->next;
    // 返回左起第二个元素即原链表中的节点
    return left_head->next;
}

// 链表分割
// 这是另外一种解法：把小于 k 的节点往前提
struct Node *Partition2(struct Node *head, int k) {
    // slow_head 是虚拟头节点，指向 head
    struct Node *slow_head = &(struct Node){0, head};
    struct Node *slow = slow_head;  // slow 指向目前 <k 的节点
    struct Node *fast = head;       // fast 一步一个节点迭代
    struct Node *prev = head;       // fast 的前驱节点

    while (fast != NULL) {
        struct Node *fast_next = fast->next;
        if (fast->v < k) {
            // 移除当前节点 fast
            if (prev != NULL) prev->next = fast_next;
            // 放入到 slow 节点之后
            if (slow->next != fast) {
                fast->next = slow->next;
                slow->next = fast;
            }
            slow = fast;
        } else {
            // 只有不挪走 fast 的时候才更新 prev
            prev = fast;
        }
        fast = fast_next;
    }
    return slow_head->next;
}

// 反转链表的一个区间
// 第一种方法：头插法
struct Node *ReverseInterval1(struct Node *head, int left, int right) {
    struct Node *virtual_head = &(struct Node){0, head};
    struct Node *node = head;
    struct Node *prev = virtual_head;
    struct Node *left_bound = NULL;       // 左边界节点
    struct Node *left_bound_prev = NULL;  // 左边界节点的前驱节点

    int i = 1;

    while (node != NULL && i <= right) {
        struct Node *node_next = node->next;

        if (i == left) {
            // 初始化左边界
            left_bound = node;
            left_bound_prev = prev;
        }

        if (i > left) {  // 插入左边界之前
            prev->next = node->next;
            node->next = left_bound;
            // 此时 i > left ，说明 i == left 肯定已执行
            // left_bound_prev 必定非空
            left_bound_prev->next = node;
            // 更新左边界
            left_bound = node;
        } else {
            // 注意，只有在没有挪走 node 的时候才需要更新 prev
            prev = node;
        }

        node = node_next;
        i++;
    }

    return virtual_head->next;
}

// 反转链表的一个区间
// 第二个方法：反转区间后再缝接的方法
struct Node *ReverseInterval2(struct Node *head, int left, int right) {
    struct Node *node = head;
    struct Node *prev = NULL;
    struct Node *left_bound = NULL;   // 左边界节点
    struct Node *right_bound = NULL;  // 右边界节点
    struct Node *left_prev = NULL;    // 左边界前面的节点
    struct Node *right_next = NULL;   // 右边界后面的节点

    int i = 1;

    while (node != NULL && i <= right) {
        struct Node *node_next = node->next;

        if (i == left) {  // 记住左边界
            left_bound = node;
            left_prev = prev;
        }

        if (i == right) {  // 记住右边界
            right_bound = node;
            right_next = node_next;
        }

        // 中间区间 (left, right] 进行反转
        if (i > left && i <= right) node->next = prev;

        prev = node;
        node = node_next;
        i++;
    }

    // 缝接到原链表上
    if (left_prev != NULL) left_prev->next = right_bound;
    if (left_bound != NULL) left_bound->next = right_next;
    if (left_prev != NULL) return head;
    return right_bound;
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

void TestPartition() {
    struct Node f = {2, NULL};
    struct Node e = {5, &f};
    struct Node d = {2, &e};
    struct Node c = {3, &d};
    struct Node b = {4, &c};
    struct Node a = {1, &b};

    struct Node *h = Partition(&a, 3);
    assert(h == &a);
    assert(h->next == &d);
    assert(h->next->next == &f);
    assert(h->next->next->next == &b);
    assert(h->next->next->next->next == &c);
    assert(h->next->next->next->next->next == &e);
}

void TestPartition2() {
    struct Node f = {2, NULL};
    struct Node e = {5, &f};
    struct Node d = {2, &e};
    struct Node c = {3, &d};
    struct Node b = {4, &c};
    struct Node a = {1, &b};

    struct Node *h = Partition2(&a, 3);
    assert(h == &a);
    assert(h->next == &d);
    assert(h->next->next == &f);
    assert(h->next->next->next == &b);
    assert(h->next->next->next->next == &c);
    assert(h->next->next->next->next->next == &e);
}

void TestReverseInterval1() {
    struct Node e = {5, NULL};
    struct Node d = {4, &e};
    struct Node c = {3, &d};
    struct Node b = {2, &c};
    struct Node a = {1, &b};

    struct Node *a1 = ReverseInterval1(&a, 2, 4);
    assert(a1 == &a);
    assert(a1->next == &d);
    assert(a1->next->next == &c);
    assert(a1->next->next->next == &b);
    assert(a1->next->next->next->next == &e);
}

void TestReverseInterval2() {
    struct Node e = {5, NULL};
    struct Node d = {4, &e};
    struct Node c = {3, &d};
    struct Node b = {2, &c};
    struct Node a = {1, &b};

    struct Node *a1 = ReverseInterval2(&a, 2, 4);
    assert(a1 == &a);
    assert(a1->next == &d);
    assert(a1->next->next == &c);
    assert(a1->next->next->next == &b);
    assert(a1->next->next->next->next == &e);
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
    TestPartition();
    TestPartition2();
    TestReverseInterval1();
    TestReverseInterval2();
    return 0;
}
