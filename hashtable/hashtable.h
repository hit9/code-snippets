// 一个最简化的哈希表实现
// 采用栈上内存作为底层数组 (大小有限)
// 哈希冲突解决采用开放寻址法

#include <stdbool.h>

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
