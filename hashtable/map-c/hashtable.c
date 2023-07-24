#include "hashtable.h"

///////
// 实现
///////

// 简单哈希函数 k^2 + i 永远非负
int Hash(int k, int i, int n) { return (k * k + i) % n; }

// 初始化表格为未使用
void Init(T m[], int n) {
    for (int i = 0; i < n; i++) (&m[i])->used = false;
}

// 拷贝表格 m1 到更大的表格 m2
// 如果 m2 不足以容纳，返回 false
bool Copy(T m1[], int n1, T m2[], int n2) {
    // 初始化 m2
    Init(m2, n2);

    // 拷贝并重新哈希到 m2
    for (int i = 0; i < n1; i++) {
        T *s = &m1[i];
        if (s->used) {
            if (!Set(m2, n2, s->k, s->v)) return false;
        }
    }
    return true;
}

// 添加或更新键 k 的值为 v
// 如果 m 不足以容纳，返回 false
bool Set(T m[], int n, int k, int v) {
    for (int i = 0; i < n; i++) {
        int p = Hash(k, i, n);
        T *s = &m[p];
        // 添加或更新
        // 哈希冲突: 即 used 且 s->k != k 的情况:
        // 会继续向前 Hash 来找新的槽, 由于 i 是 Hash
        // 的入参，所以下一位置不同于当前位置
        if (!s->used || s->k == k) {
            s->k = k;
            s->v = v;
            s->used = true;
            return true;
        }
    }
    return false;
}

// 获取键 k 的值，如果不存在返回 v0
int Get(T m[], int n, int k, int v0) {
    for (int i = 0; i < n; i++) {
        int p = Hash(k, i, n);
        T *s = &m[p];
        if (s->used && s->k == k) return s->v;
    }
    return v0;
}

// 测试键 k 是否在表 m 中
bool Has(T m[], int n, int k) {
    for (int i = 0; i < n; i++) {
        int p = Hash(k, i, n);
        T *s = &m[p];
        if (s->used && s->k == k) return true;
    }
    return false;
}

// 弹出键 k，返回它的值。如果不存在返回 v0
int Pop(T m[], int n, int k, int v0) {
    for (int i = 0; i < n; i++) {
        int p = Hash(k, i, n);
        T *s = &m[p];
        if (s->used && s->k == k) {
            s->used = false;
            return s->v;
        }
    }
    return v0;
}

// 计数有多少键值对
int Count(T m[], int n) {
    int j = 0;
    for (int i = 0; i < n; i++) {
        T *s = &m[i];
        if (s->used) j++;
    }
    return j;
}
