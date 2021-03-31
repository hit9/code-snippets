//////////
// 辅助数据结构 - 队列
//////////

#include "queue.h"

#include <stdbool.h>
#include <stdlib.h>

// 创建一个队列节点
QNode *NewQNode(void *v) {
    QNode *node = malloc(sizeof(QNode));
    node->v = v;
    node->next = NULL;
    return node;
}

// 释放一个队列节点
void FreeQNode(QNode *node) { free(node); }

// 创建一个队列
Queue *NewQueue() {
    Queue *q = malloc(sizeof(Queue));
    q->head = NULL;
    q->tail = NULL;
    q->length = 0;
    return q;
}

// 是否队空？
bool IsQueueEmpty(Queue *q) {
    if (q == NULL || q->length == 0) return true;
    return false;
}

// 获取队列头, 空返回 NULL
void *QueueFront(Queue *q) {
    if (IsQueueEmpty(q)) return NULL;
    return q->head->v;
}

// 数据入队
void QueuePush(Queue *q, void *v) {
    if (q == NULL) return;

    QNode *node = NewQNode(v);

    if (IsQueueEmpty(q)) {
        q->head = node;
        q->tail = node;
    } else {
        q->tail->next = node;
        q->tail = node;
    }
    q->length++;
}

// 队头出队, 空返回 NULL
void *QueuePop(Queue *q) {
    if (IsQueueEmpty(q)) return NULL;

    QNode *head = q->head;

    if (q->tail == head) q->tail = NULL;
    q->head = head->next;
    q->length--;

    void *v = head->v;
    FreeQNode(head);
    return v;
}

// 释放一个队列
void FreeQueue(Queue *q) {
    while (!IsQueueEmpty(q)) QueuePop(q);
    free(q);
}
// 获取队列大小
int QueueSize(Queue *q) {
    if (q == NULL) return 0;
    return q->length;
}
