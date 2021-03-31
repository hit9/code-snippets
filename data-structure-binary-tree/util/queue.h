// 辅助数据结构 - 队列

#include <stdbool.h>

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
