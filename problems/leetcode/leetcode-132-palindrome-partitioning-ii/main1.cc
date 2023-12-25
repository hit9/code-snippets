#include <string>

using namespace std;

#define N 2010

namespace pam {
int sz, tot, last;
int tree[N][26], len[N], fail[N];
int cnt[N], dif[N], slink[N];
char s[N];

int node(int l) {  // 建立一个长度为 l 的新节点
    sz++;
    len[sz] = l;
    fail[sz] = 0;
    cnt[sz] = 0;
    return sz;
}

void init() {  // 初始化
    memset(tree, 0, sizeof tree);
    sz = -1;
    tot = 0;
    last = 0;
    s[0] = '$';
    node(0);
    node(-1);
    fail[0] = 1;
}

int up(int x) {  // 找到后缀回文
    while (s[tot - len[x] - 1] != s[tot]) x = fail[x];
    return x;
}

void insert(char ch) {  // 建树
    s[++tot] = ch;
    int c = ch - 'a';
    int now = up(last);
    if (!tree[now][c]) {
        int x = node(len[now] + 2);
        fail[x] = tree[up(fail[now])][c];
        tree[now][c] = x;
        dif[x] = len[x] - len[fail[x]];
        slink[x] = dif[x] == dif[fail[x]] ? slink[fail[x]] : fail[x];
    }
    last = tree[now][c];
    cnt[last]++;
}
}  // namespace pam

using pam::dif;
using pam::fail;
using pam::len;
using pam::slink;
int f[N], g[N];

class Solution {
   public:
    int minCut(string s) {
        int n = s.size();

        f[0] = -1;
        memset(g, 0x3f, sizeof g);

        pam::init();

        for (int i = 1; i <= n; i++) {
            f[i] = f[i - 1] + 1;
            pam::insert(s[i - 1]);

            for (int x = pam::last; x > 1; x = slink[x]) {
                g[x] = f[i - len[slink[x]] - dif[x]] + 1;
                if (dif[x] == dif[fail[x]]) g[x] = min(g[x], g[fail[x]]);
                f[i] = min(f[i], g[x]);
            }
            if (i >= 2 && s[i - 2] == s[i - 1]) f[i] = min(f[i], f[i - 2] + 1);
        }
        return f[n];
    }
};
