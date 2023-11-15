// https://leetcode.cn/problems/find-median-from-data-stream/description/?envType=study-plan-v2&envId=top-100-liked
// 295. 数据流的中位数
// 中位数是有序整数列表中的中间值。如果列表的大小是偶数，则没有中间值，中位数是两个中间值的平均值。
// 例如 arr = [2,3,4] 的中位数是 3 。
// 例如 arr = [2,3] 的中位数是 (2 + 3) / 2 = 2.5 。
// 实现 MedianFinder 类:
// 1. MedianFinder() 初始化 MedianFinder 对象。
// 2. void addNum(int num) 将数据流中的整数 num 添加到数据结构中。
// 3. double findMedian() 返回到目前为止所有元素的中位数。与实际答案相差 10-5
// 以内的答案将被接受。 示例：输入
// ["MedianFinder", "addNum", "addNum", "findMedian", "addNum", "findMedian"]
// [[], [1], [2], [], [3], []]
// 输出 [null, null, null, 1.5, null, 2.0]

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class MedianFinder {
   public:
    // q1 大根堆，存放比中位数小的
    // q2 小根堆，存放比中位数大的
    // 中位数: len(q1) > len(q2) 的情况: top(q1)
    //         len(q1) = len(q2) 的情况: (top(q1) + top(q2)) / 2.0
    priority_queue<int, vector<int>> q1;
    priority_queue<int, vector<int>, greater<int>> q2;

    MedianFinder() {}

    // 如果比 q2 的堆顶大，则放入 q2
    // 如果比 q1 的堆顶小，则放入 q1
    // 需要保证 q1.size() 和 q2.size() 大，且差距不超过 1
    void addNum(int num) {
        if (!q2.empty() && num > q2.top()) {
            q2.push(num);
            if (q2.size() > q1.size()) {
                auto v = q2.top();
                q2.pop();
                q1.push(v);
            }
        } else {
            q1.push(num);
            if (q2.size() + 1 < q1.size()) {
                auto v = q1.top();
                q1.pop();
                q2.push(v);
            }
        }
    }

    double findMedian() {
        if (q1.size() > q2.size()) return q1.top();
        return (q1.top() + q2.top()) / 2.0;
    }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */

int main(void) {
    MedianFinder f;
    f.addNum(1);
    f.addNum(2);
    f.addNum(3);
    f.addNum(4);
    f.addNum(5);
    cout << f.findMedian() << endl;  // 3
    return 0;
}
