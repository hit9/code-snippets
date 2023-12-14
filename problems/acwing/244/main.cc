// https://www.acwing.com/problem/content/description/245/

#include <iostream>
#include <vector>
using namespace std;
class BIT {
   private:
    int n;
    vector<int> c;

   public:
    explicit BIT(int n) : n(n), c(vector<int>(n + 1, 0)){};
    int lowbit(int x) { return x & -x; }
    void add(int x, int v) {
        for (; x <= n; x += lowbit(x)) c[x] += v;
    }
    int ask(int x) {
        int ans = 0;
        for (; x; x -= lowbit(x)) ans += c[x];
        return ans;
    }
};

// n 头奶牛, a 是大小为 n+1 的从 2 开始的输入数组
// ans 是结果数组
void solve(int n, vector<int>& a, vector<int>& ans) {
    // 一个数组 p = [1,1,1,1,...]
    // b 动态维护其前缀和
    BIT b(n);
    for (int i = 1; i <= n; i++) b.add(i, 1);

    // 倒序找身高
    // 最后 BIT 中应该还剩余一个 1, 让 a[1] = 0
    a[1] = 0;
    for (int i = n; i >= 1; i--) {
        // 二分答案找第 a[i]+1 个 1 的位置
        // 其实就是找 Sum(x) >= a[i] + 1 的左界
        int l = 1;
        int r = n;
        while (l < r) {
            int m = (l + r) >> 1;
            if (b.ask(m) >= a[i] + 1)
                r = m;
            else
                l = m + 1;
        }
        ans[i] = l;
        // 找到之后维护下 BIT
        b.add(l, -1);
    }
}

int main(void) {
    int n;
    cin >> n;
    getchar();
    vector<int> a(n + 1);
    for (int i = 2; i <= n; i++) cin >> a[i];
    getchar();
    vector<int> ans(n + 1);
    solve(n, a, ans);
    for (int i = 1; i <= n; i++) cout << ans[i] << endl;
    return 0;
}
