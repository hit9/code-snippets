#include <iostream>
#include <vector>

using namespace std;

// LIS 问题求解
int LIS(vector<int>& nums) {
    vector<int> p{nums[0]};

    for (int i = 1; i < nums.size(); i++) {
        if (auto num = nums[i]; num > p.back())
            p.push_back(num);
        else {
            auto j = lower_bound(p.begin(), p.end(), num);
            *j = num;
        }
    }
    return p.size();
}

int main(void) {
    // 处理输入
    int n;
    cin >> n;
    getchar();  // '\n'

    int c;  // 当前输入

    // a[i] 记录数字 i-1 的所在的位置
    vector<int> a(n, 0);
    for (int i = 0; i < n; i++) {
        cin >> c;
        a[c - 1] = i;
    }
    getchar();  // '\n'

    // b[i] 记录输入的数字 k, 对应的 k-1 在 a[i] 中的出现的位置
    vector<int> b(n, 0);
    for (int i = 0; i < n; i++) {
        cin >> c;
        b[i] = a[c - 1];
    }

    getchar();  // '\n'
    // 公共子序列的长度就是 b 的最长上升序列
    cout << LIS(b) << endl;
    return 0;
}
