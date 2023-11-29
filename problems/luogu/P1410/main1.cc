// https://www.luogu.com.cn/problem/P1410
//
// 目前这个 DFS 会超时..

#include <iostream>
#include <vector>

using namespace std;

// nums 是原数组
// na 是 a 的大小, nb 是 b 的大小
// a 是数组 a 的最后一个数字
// b 是数组 a 的最后一个数字
// i 是当前 nums 中的迭代下标
// k 是 nums.size()/2
bool dfs(vector<int>& nums, int n, int k, int na, int a, int nb, int b, int i,
         vector<int>& p, vector<int>& q) {
    if (na == k && nb == k) return true;
    if (i >= n) return false;

    // 剪枝：如果右侧的最大值比当前两个值都小，就提前退出
    if (nums[q[i]] <= a && nums[q[i]] <= b) return false;

    // 如果右侧的最大值的位置太靠左，就提前退出
    if (q[i] < k - 1) return false;

    // 剪枝：如果右侧存在一个最小值比两个当前值都小，就提前退出
    if (nums[p[i]] <= a && nums[p[i]] <= b) return false;

    // 如果右侧最小值的位置太靠右, 就提前退出
    if (nums[p[i]] > a && nums[p[i]] <= b && k - na > (n - p[i])) {
        return false;
    }
    if (nums[p[i]] > b && nums[p[i]] <= a && k - nb > (n - p[i])) {
        return false;
    }
    if (nums[p[i]] > a && nums[p[i]] > b &&
        (n - p[i]) < std::min(k - na, k - nb)) {
        return false;
    }

    // 平衡填数，如果 na 已经行进太多，则先填 b
    // 这样 a 和 b 两个子数组的大小不至于相差太多
    if (na > nb + 1) return dfs(nums, n, k, nb, b, na, a, i, p, q);

    // 考虑 nums[i] 放 a 数组
    int x = nums[i];
    if (na < k && x > a) {
        if (dfs(nums, n, k, na + 1, x, nb, b, i + 1, p, q)) return true;
    }

    // 剪枝: 另一个已经满了, 但是上面考察放入 a 仍不行，
    // 则剩下的无法把 a 构成大小为 k 的递增序列
    if (nb == k) return false;

    // 考虑 nums[i] 放 b 数组
    if (nb < k && x > b) {
        if (dfs(nums, n, k, na, a, nb + 1, x, i + 1, p, q)) return true;
    }
    if (na == k) return false;
    return false;
}

bool check(vector<int>& nums, vector<int>& p, vector<int>& q, int n) {
    // 提前预处理出数组 p
    // p[i] 记录右侧区间上 [i..] 的最小值的位置
    p[n - 1] = n - 1;
    for (int i = n - 2; i >= 0; i--) {
        if (nums[i] < nums[p[i + 1]])
            p[i] = i;
        else
            p[i] = p[i + 1];
    }

    // q[i] 记录右侧区间上 [i..] 的最大值的位置
    q[n - 1] = n - 1;
    for (int i = n - 2; i >= 0; i--) {
        if (nums[i] > nums[q[i + 1]])
            q[i] = i;
        else
            q[i] = q[i + 1];
    }

    // 可以直接先假定第一个元素放入 a
    return dfs(nums, n, n / 2, 1, nums[0], 0, -1, 1, p, q);
}

int main(void) {
    vector<int> nums(2001);
    vector<int> p(2001);  // 辅助数组: 记录右侧最小值的位置
    vector<int> q(2001);  // 辅助数组: 记录右侧最大值的位置

    // 多组测试数据
    while (1) {
        // 输入
        int n;
        cin >> n;
        if (cin.eof()) break;

        // 输入数组
        for (int j = 0; j < n; j++) cin >> nums[j];

        // 调用
        if (check(nums, p, q, n))
            cout << "Yes!" << endl;
        else
            cout << "No!" << endl;
    }
    return 0;
}
