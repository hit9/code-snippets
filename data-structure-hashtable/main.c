// 一个最简化的哈希表实现
// 哈希冲突解决采用开放寻址法

#include <assert.h>  // for assert
#include <stdbool.h>
#include <stdio.h>  // for printf

///////
// 声明
///////

// 槽位
typedef struct {
    int k;
    int v;
    bool used;
} T;

void Init(T m[], int n);                    // 初始化
bool Copy(T m1[], int n1, T m2[], int n2);  // 拷贝
bool Set(T m[], int n, int k, int v);       // 添加 或 更新
int Get(T m[], int n, int k, int v0);       // 获取
bool Has(T m[], int n, int k);              // 判断
int Pop(T m[], int n, int k, int v0);       // 弹出
int Count(T m[], int n);                    // 计数

///////
// 实现
///////

// 简单哈希函数
int Hash(int k, int i, int n) { return (k * (k + 3) + i) % n; }

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
        if (!s->used || s->k == k) {  // 添加或更新
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

///////
// 样例
///////

int main(void) {
    // 初始化
    int n1 = 13;
    T m1[n1];
    Init(m1, n1);

    // 插入和查询
    int k1 = 172;
    int v1 = 123;
    Set(m1, n1, k1, v1);

    assert(Has(m1, n1, k1) == true);      // 存在
    assert(Has(m1, n1, 15738) == false);  // 不存在

    assert(Get(m1, n1, k1, 0) == v1);    // 存在
    assert(Get(m1, n1, 15738, 0) == 0);  // 不存在

    // 扩展
    int n2 = n1 + n1;
    T m2[n2];
    Copy(m1, n1, m2, n2);

    assert(Get(m2, n2, k1, 0) == v1);  // 数据已迁移

    // 删除
    assert(Pop(m2, n2, k1, 0) == v1);  // 存在
    assert(Pop(m2, n2, k1, 0) == 0);   // 已不存在

    // 打印
    Set(m2, n2, 123, 132);
    Set(m2, n2, 678, 687);
    Set(m2, n2, 456, 465);
    Set(m2, n2, 789, 798);

    for (int i = 0; i < n2; i++) {
        if (m2[i].used) {
            int k = m2[i].k;
            int v = m2[i].v;
            printf("%d => %d \n", k, v);
        }
    }

    return 0;
}
