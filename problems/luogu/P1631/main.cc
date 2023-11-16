// https://www.luogu.com.cn/problem/P1631

#include <iostream>
#include <queue>
#include <utility>
#include <vector>

using namespace std;
using P = pair<int, int>;  // index of a and b.
int main(void) {
    // 输入
    int n;
    cin >> n;
    getchar();

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    getchar();

    vector<int> b(n);
    for (int i = 0; i < n; i++) cin >> b[i];
    getchar();

    // 输出结果
    auto cmp = [&](const auto &x, const auto &y) {
        return a[x.first] + b[x.second] > a[y.first] + b[y.second];
    };
    // 小顶堆，维护的是 N 个最小的 a[i] + b[j] 的下标 (i, j)
    priority_queue<P, vector<P>, decltype(cmp)> q(cmp);

    // a[i], b[0] 入队
    for (int i = 0; i < n; i++) q.push({i, 0});

    // 置换: 现在堆中的是每行的第一个元素, 但不一定是全局最小的 N 个。
    // 但是！全局最小的一定在其中。因为每一行的行头一定是行内最小。
    // 弹出这个最小值，并输出。进一步考虑其后面的元素，因为后面的元素和其他的
    // N-1 个仍需要比较。
    //
    // 根本上，每一行最具竞争力的是行头。
    //
    //  +---------> 增大
    //  |
    //  |  a[0]+b[0], a[0]+b[1], ...
    //  |  a[1]+b[0], a[1]+b[1], ...
    //  |  a[2]+b[0], a[2]+b[1], ...
    //  |  ....
    //  v
    // 增大
    while (n--) {
        auto [i, j] = q.top();
        q.pop();
        cout << a[i] + b[j] << " ";
        q.push({i, j + 1});
    }

    cout << endl;
    return 0;
}
