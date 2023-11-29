// https://www.luogu.com.cn/problem/P1410

#include <iostream>
#include <vector>

using namespace std;

// nums 是原数组
// na 是 a 的大小, nb 是 b 的大小
// a 是数组 a 的最后一个数字
// b 是数组 a 的最后一个数字
// i 是当前 nums 中的迭代下标
// k 是 nums.size()/2
bool dfs(vector<int>& nums, int n, int k, int na, int a, int nb, int b, int i) {
    if (na == k && nb == k) return true;
    if (i >= n) return false;

    // 平衡填数，如果 na 已经行进太多，则先填 b
    // 这样 a 和 b 两个子数组的大小不至于相差太多
    if (na > nb + 1) return dfs(nums, n, k, nb, b, na, a, i);

    // 考虑 nums[i] 放 a 数组
    int x = nums[i];
    if (na < k && x > a) {
        if (dfs(nums, n, k, na + 1, x, nb, b, i + 1)) return true;
    }

    // 剪枝: 另一个已经满了, 但是上面考察放入 a 仍不行，
    // 则剩下的无法把 a 构成大小为 k 的递增序列
    if (nb == k) return false;

    // 考虑 nums[i] 放 b 数组
    if (nb < k && x > b) {
        if (dfs(nums, n, k, na, a, nb + 1, x, i + 1)) return true;
    }
    if (na == k) return false;
    return false;
}

bool check(vector<int>& nums, int n) {
    // 可以直接先假定第一个元素放入 a
    return dfs(nums, n, n / 2, 1, nums[0], 0, -1, 1);
}

int main(void) {
    vector<int> nums(2001);
    // 多组测试数据
    while (1) {
        // 输入
        int n;
        cin >> n;
        if (cin.eof()) break;

        // 输入数组
        for (int j = 0; j < n; j++) cin >> nums[j];

        // 调用
        if (check(nums, n))
            cout << "Yes!" << endl;
        else
            cout << "No!" << endl;
    }
    return 0;
}
