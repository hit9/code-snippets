#include <iostream>
#include <queue>
#include <vector>
using namespace std;
int main(void) {
    int n;
    cin >> n;
    getchar();

    vector<int> a(n, 0);
    for (int i = 0; i < n; i++) cin >> a[i];
    getchar();

    // q1 是大顶堆
    priority_queue<int> q1;
    // q2 是小顶堆
    priority_queue<int, vector<int>, greater<int>> q2;

    // q1 保持比 q2 多一个元素
    // q1 的堆顶就是中位数

    for (int i = 0; i < n; i++) {
        // 如果小于 q1 堆顶，则加入到 q1, 否则给 q2
        if (q1.empty() || q1.top() > a[i])
            q1.push(a[i]);
        else
            q2.push(a[i]);

        // 两个堆平衡, 保持 q1 最多比 q2 多一个元素
        while (q1.size() > q2.size() + 1) {
            // q1 多，则向 q2  转移
            q2.push(q1.top());
            q1.pop();
        }

        while (q2.size() + 1 > q1.size()) {
            // q2 多，则向 q1 转移
            q1.push(q2.top());
            q2.pop();
        }

        // 两个 while 只有一个会发生

        if (i%2 == 0) cout << q1.top() << endl;
    }
    return 0;
}
