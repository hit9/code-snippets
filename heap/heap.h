// 数据结构堆的最小化实现（最小堆）
// https://writings.sh/post/data-structure-heap-and-common-problems

// 采用数组表示堆
//
//           0
//      1         2
//   3     4   5      6
//
// 父亲 i => 左孩子 j1=2*i+1，右孩子 j2=j1+1
// 孩子 j => 父亲 i=(j-1)/2

void Swap(int a[], int i, int j);    // 交换
void Up(int a[], int j);             // 上浮
void Down(int a[], int n, int i);    // 下沉
void Build(int a[], int n);          // 堆化
int Push(int a[], int n, int v);     // 插入
int Pop(int a[], int n);             // 删除
int Top(int a[]);                    // 堆顶
int Replace(int a[], int n, int v);  // 替换
