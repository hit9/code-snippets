#include <iostream>
#include <vector>
using namespace std;

// 原地离散化，返回离散化后的值域最值 m
// 假设原数组 a 下标从 0 开始
int discrete(vector<int>& a) {
    // ①  拷贝一份
    vector<int> p(a.begin(), a.end());

    // ② 排序
    sort(p.begin(), p.end());

    // ③ 去重
    int m = unique(p.begin(), p.end()) - p.begin();

    // ④ 找左界，原地替换为下标
    for (int i = 0; i < a.size(); i++) {
        // 映射到 1~m
        a[i] = lower_bound(p.begin(), p.begin() + m, a[i]) - p.begin() + 1;
    }
    return m;
}

int main(void) {
    vector<int> a{-9281903, 5, 290389, 99298348, -88723, 17300284, 5, 290389};
    discrete(a);
    for (int i = 0; i < a.size(); i++) cout << a[i] << ",";
    cout << endl;
    return 0;
}
