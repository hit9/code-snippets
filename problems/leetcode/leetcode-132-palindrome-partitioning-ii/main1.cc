#include <iostream>
#include <string>

using namespace std;

#define maxn 2010

namespace pam {
int sz, tot, last;
int ch[maxn][26], len[maxn], fail[maxn];
int cnt[maxn], dep[maxn], dif[maxn], slink[maxn];
char s[maxn];

int node(int l) {  // 建立一个长度为 l 的新节点
    sz++;
    memset(ch[sz], 0, sizeof(ch[sz]));
    len[sz] = l;
    fail[sz] = 0;
    cnt[sz] = 0;
    dep[sz] = 0;
    return sz;
}

void clear() {  // 初始化
    sz = -1;
    last = 0;
    s[tot = 0] = '$';
    node(0);
    node(-1);
    fail[0] = 1;
}

int getfail(int x) {  // 找到后缀回文
    while (s[tot - len[x] - 1] != s[tot]) x = fail[x];
    return x;
}

void insert(char c) {  // 建树
    s[++tot] = c;
    int now = getfail(last);
    if (!ch[now][c - 'a']) {
        int x = node(len[now] + 2);
        fail[x] = ch[getfail(fail[now])][c - 'a'];
        dep[x] = dep[fail[x]] + 1;
        ch[now][c - 'a'] = x;
        dif[x] = len[x] - len[fail[x]];
        if (dif[x] == dif[fail[x]])
            slink[x] = slink[fail[x]];
        else
            slink[x] = fail[x];
    }
    last = ch[now][c - 'a'];
    cnt[last]++;
}
}  // namespace pam

using pam::dif;
using pam::fail;
using pam::len;
using pam::slink;
int f[maxn], g[maxn];

class Solution {
   public:
    int minCut(string s) {
        int n = s.size();

        f[0] = -1;
        memset(g, 0x3f, sizeof g);

        pam::clear();

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


