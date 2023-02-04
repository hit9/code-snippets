// 辅助函数和数据结构

#include <stdbool.h>

// 动态数组（整型）
typedef struct _IntArray {
    int *a;
    int n;
    int cap;
} IntArray;

IntArray *NewIntArray();
void FreeIntArray(IntArray *a);
bool IntArrayPush(IntArray *a, int v);
int IntArraySize(IntArray *a);
int IntArrayPop(IntArray *a);
int *IntArrayUnwrap(IntArray *a);

// 动态数组（一般类型）
typedef struct _Array {
    void **a;
    int n;
    int cap;
} Array;

Array *NewArray();
void FreeArray(Array *a);
bool ArrayPush(Array *a, void *v);
int ArraySize(Array *a);
void *ArrayPop(Array *a);
void **ArrayUnwrap(Array *a);

// 栈
typedef struct _Stack {
    Array *a;
} Stack;

Stack *NewStack();
void FreeStack(Stack *stack);
bool StackPush(Stack *stack, void *v);
void *StackPop(Stack *stack);
bool IsStackEmpty(Stack *stack);
void *StackTop(Stack *stack);

// 单端队列
typedef struct _QNode {
    void *v;
    struct _QNode *next;
} QNode;

typedef struct _Queue {
    int length;
    QNode *head;
    QNode *tail;
} Queue;

QNode *NewQNode(void *v);     // 创建队列节点
void FreeQNode(QNode *node);  // 释放队列节点

Queue *NewQueue();                  // 创建队列
void FreeQueue(Queue *q);           // 释放队列
bool IsQueueEmpty(Queue *q);        // 是否队空？
void *QueueFront(Queue *q);         // 获取队头
void QueuePush(Queue *q, void *v);  // 数据入队
void *QueuePop(Queue *q);           // 队头出队
int QueueSize(Queue *q);            // 队列大小

// 辅助函数
bool IsArrayEqual(int a[], int m, int b[], int n);
void PrintIntArray(int a[], int n);
