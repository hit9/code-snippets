// https://www.luogu.com.cn/problem/P3374

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
    int ask(int x, int y) { return ask(y) - ask(x - 1); }
};

int main(void) {
    int n;
    int m;
    cin >> n >> m;
    getchar();

    BIT b(n + 1);

    for (int i = 1; i <= n; i++) {
        int v;
        cin >> v;
        b.add(i, v);
    }

    getchar();

    while (m--) {
        int op, x, y;
        cin >> op >> x >> y;
        getchar();
        if (op == 1) {
            b.add(x, y);
        } else {
            cout << b.ask(x, y) << endl;
        }
    }

    return 0;
}
