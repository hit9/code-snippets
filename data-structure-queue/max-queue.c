// 最大值队列 - 在队列的基础上，实现一个常数时间的最大值函数
// https://writings.sh/post/monotonous-stack-and-monotonous-queue
// https://leetcode-cn.com/problems/dui-lie-de-zui-da-zhi-lcof/
// 要求 PushBack() PopFront() Max() 三个函数平均时间复杂度 O(1)

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>  // for malloc, free

////////
// 声明
////////

// 思路：
// 两个队列实现
// 一个队列 a 是正常的先进先出队列
// 另一个队列 b 单调递减双端队列
// 此文件只需看 PushBack 和 PopFront 函数的而实现，其他都是辅助函数。

typedef struct _QNode {
    int value;
    struct _QNode *next;
    struct _QNode *prev;
} QNode;

typedef struct _Queue {
    int length;
    QNode *head;
    QNode *tail;
} Queue;

typedef struct {
    Queue *a;
    Queue *b;  // 单调递减
} MaxQueue;

MaxQueue *NewMaxQueue();
void PushBack(MaxQueue *q, int value);
int PopFront(MaxQueue *q);
int Max(MaxQueue *q);
void FreeMaxQueue(MaxQueue *q);

QNode *NewNode(int value);
void FreeNode(QNode *node);

Queue *NewQueue();
bool QueueIsEmpty(Queue *q);

void QueuePushFront(Queue *q, int value);
int QueuePopFront(Queue *q);
void QueuePushBack(Queue *q, int value);
int QueuePopBack(Queue *q);
int QueueGetFront(Queue *q);
int QueueGetBack(Queue *q);
void FreeQueue(Queue *q);

////////////////////
// 实现最大值队列
////////////////////

MaxQueue *NewMaxQueue() {
    MaxQueue *q = malloc(sizeof(MaxQueue));
    q->a = NewQueue();
    q->b = NewQueue();
    return q;
}

void PushBack(MaxQueue *q, int value) {
    QueuePushBack(q->a, value);
    while (!QueueIsEmpty(q->b) && QueueGetBack(q->b) < value)
        QueuePopBack(q->b);
    QueuePushBack(q->b, value);
}

int PopFront(MaxQueue *q) {
    if (QueueIsEmpty(q->a)) return -1;
    int value = QueuePopFront(q->a);
    if (value == QueueGetFront(q->b)) QueuePopFront(q->b);
    return value;
}

int Max(MaxQueue *q) {
    if (QueueIsEmpty(q->b)) return -1;
    return QueueGetFront(q->b);
}

void FreeMaxQueue(MaxQueue *q) {
    FreeQueue(q->a);
    FreeQueue(q->b);
    free(q);
}

////////////////////
// 实现队列 （辅助）
////////////////////

QNode *NewNode(int value) {
    QNode *node = malloc(sizeof(QNode));
    node->next = NULL;
    node->prev = NULL;
    node->value = value;
    return node;
}

void FreeNode(QNode *node) { free(node); }

Queue *NewQueue() {
    Queue *q = malloc(sizeof(Queue));
    q->length = 0;
    q->head = NULL;
    q->tail = NULL;
    return q;
}

bool QueueIsEmpty(Queue *q) {
    if (q->length == 0) return true;
    return false;
}

void QueuePushFront(Queue *q, int value) {
    QNode *node = NewNode(value);

    if (QueueIsEmpty(q)) {
        q->head = node;
        q->tail = node;
    } else {
        node->next = q->head;
        q->head->prev = node;
        q->head = node;
    }
    q->length++;
}

int QueuePopFront(Queue *q) {
    if (QueueIsEmpty(q)) return -1;

    QNode *head = q->head;
    QNode *head_next = head->next;

    q->head = head_next;
    if (head_next != NULL) head_next->prev = NULL;
    if (q->tail == head) q->tail = NULL;
    q->length--;

    int value = head->value;
    FreeNode(head);
    return value;
}

void QueuePushBack(Queue *q, int value) {
    QNode *node = NewNode(value);
    if (QueueIsEmpty(q)) {
        q->head = node;
        q->tail = node;
    } else {
        q->tail->next = node;
        node->prev = q->tail;
        q->tail = node;
    }
    q->length++;
}

int QueuePopBack(Queue *q) {
    if (QueueIsEmpty(q)) return -1;

    QNode *tail = q->tail;
    QNode *tail_prev = tail->prev;

    q->tail = tail_prev;
    if (tail_prev != NULL) tail_prev->next = NULL;
    if (q->head == tail) q->head = NULL;

    q->length--;

    int value = tail->value;
    FreeNode(tail);
    return value;
}

int QueueGetFront(Queue *q) {
    if (QueueIsEmpty(q)) return -1;
    return q->head->value;
}

int QueueGetBack(Queue *q) {
    if (QueueIsEmpty(q)) return -1;
    return q->tail->value;
}

void FreeQueue(Queue *q) {
    while (!QueueIsEmpty(q)) QueuePopFront(q);
    free(q);
}

int main(void) {
    MaxQueue *q = NewMaxQueue();
    PushBack(q, 1);
    PushBack(q, 4);
    PushBack(q, 3);
    PushBack(q, 2);
    assert(Max(q) == 4);
    assert(PopFront(q) == 1);
    assert(PopFront(q) == 4);
    assert(Max(q) == 3);
    FreeMaxQueue(q);
    return 0;
}
