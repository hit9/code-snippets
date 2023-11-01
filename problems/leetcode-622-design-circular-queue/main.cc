// https://leetcode.cn/problems/design-circular-queue
// 622. 设计循环队列
// 设计你的循环队列实现。 循环队列是一种线性数据结构，其操作表现基于
// FIFO（先进先出）原则并且队尾被连接在队首之后以形成一个循环。它也被称为“环形缓冲器”。
// 循环队列的一个好处是我们可以利用这个队列之前用过的空间。在一个普通队列里，一旦一个队列满了，
// 我们就不能插入下一个元素，即使在队列前面仍有空间。
// 但是使用循环队列，我们能使用这些空间去存储新的值。
// 你的实现应该支持如下操作：

//    MyCircularQueue(k): 构造器，设置队列长度为 k 。
//    Front: 从队首获取元素。如果队列为空，返回 -1 。
//    Rear: 获取队尾元素。如果队列为空，返回 -1 。
//    enQueue(value): 向循环队列插入一个元素。如果成功插入则返回真。
//    deQueue(): 从循环队列中删除一个元素。如果成功删除则返回真。
//    isEmpty(): 检查循环队列是否为空。
//    isFull(): 检查循环队列是否已满

#include <cstring>
#include <iostream>

// 环形队列设计
//
// [-----+----+------]
//       ^    ^
//  队尾 e    h 队头
//  e 是队尾指针
//  h 是队头指针
//
// Push 过程:
//  如果 n + 1 + h 没有越右侧界，则右侧追加，h 指针不动
//  放入到左侧 e 处，e 指针右移++
//
// Pop 过程:
//  如果 h 没有到达右侧边界, 则h++
//  否则, h 回 0, e 回 0, h++
class MyCircularQueue {
   private:
    int k;   // 容量
    int n;   // 计数
    int *a;  // 连续内存指针
    int e;   // 队尾指针，开
    int h;   // 队头指针，闭
   public:
    MyCircularQueue(int k) : k(k), e(0), h(0), n(0) {
        a = new int[k];
        std::memset(a, 0, k);
    }

    bool enQueue(int value) {
        if (n == k) return false;
        if (h + n + 1 <= k)  // 队尾不会越过右界, 添加到 h+n 处
            a[h + n] = value;
        else  // 添加到左侧, e 的左边
            a[e++] = value;
        n++;
        return true;
    }

    bool deQueue() {
        if (n == 0) return false;

        // 恰好到达右边界, 回零
        if (h == k - 1) {
            h = 0;
            e = 0;  // e 也要回零
        } else {
            h++;
        }
        // 出队
        n--;
        return true;
    }

    int Front() {
        if (n == 0) return -1;
        return a[h];
    }

    int Rear() {
        if (n == 0) return -1;
        if (e > 0) return a[e - 1];  // 队尾在左侧
        return a[h + n - 1];         // 队尾在右侧
    }

    bool isEmpty() { return n == 0; }

    bool isFull() { return n == k; }
};

/**
 * Your MyCircularQueue object will be instantiated and called as such:
 * MyCircularQueue* obj = new MyCircularQueue(k);
 * bool param_1 = obj->enQueue(value);
 * bool param_2 = obj->deQueue();
 * int param_3 = obj->Front();
 * int param_4 = obj->Rear();
 * bool param_5 = obj->isEmpty();
 * bool param_6 = obj->isFull();
 */

int main(void) {
    auto q = new MyCircularQueue(2);
    q->enQueue(4);
    q->enQueue(9);
    std::cout << q->Front() << std::endl;
    std::cout << q->deQueue() << std::endl;
    std::cout << q->Front() << std::endl;

    return 0;
}
