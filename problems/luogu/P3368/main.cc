#include <iostream>
#include <vector>

using namespace std;

class BIT {
   private:
    int n;
    vector<int> c;

   public:
    explicit BIT(int n) : n(n), c(vector<int>(n + 1, 0)) {}
    inline int lowbit(int x) { return x & -x; }
    void add(int x, int d) {
        for (; x <= n; x += lowbit(x)) c[x] += d;
    }
    int ask(int x) {
        int ans = 0;
        for (; x; x -= lowbit(x)) ans += c[x];
        return ans;
    }
};

int main(void) {
    int n, m;
    cin >> n >> m;
    getchar();

    vector<int> a(n + 1, 0);
    for (int i = 1; i <= n; i++) cin >> a[i];
    getchar();

    // 记录 a 的初始值
    vector<int> a1(a.begin(), a.end());

    BIT b(n + 1);

    while (m--) {
        int op = 0;
        cin >> op;
        if (op == 1) {  // 区间增加
            int x, y, k;
            cin >> x >> y >> k;
            getchar();

            b.add(x, k);
            b.add(y + 1, -k);

        } else {  // 单点查询
            int x1;
            cin >> x1;
            getchar();

            cout << b.ask(x1) + a1[x1] << endl;
        }
    }
    return 0;
}
