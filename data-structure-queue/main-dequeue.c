// 双端队列实现

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>  // for malloc, free

typedef struct _QNode {
    int value;
    struct _QNode *next;
    struct _QNode *prev;
} QNode;

QNode *NewNode(int value) {
    QNode *node = malloc(sizeof(QNode));
    node->next = NULL;
    node->prev = NULL;
    node->value = value;
    return node;
}

void FreeNode(QNode *node) { free(node); }

typedef struct _Queue {
    int length;
    QNode *head;
    QNode *tail;
} Queue;

Queue *NewQueue() {
    Queue *q = malloc(sizeof(Queue));
    q->length = 0;
    q->head = NULL;
    q->tail = NULL;
    return q;
}

bool IsEmpty(Queue *q) {
    if (q->length == 0) return true;
    return false;
}

void PushFront(Queue *q, int value) {
    QNode *node = NewNode(value);

    if (IsEmpty(q)) {
        q->head = node;
        q->tail = node;
    } else {
        node->next = q->head;
        q->head->prev = node;
        q->head = node;
    }
    q->length++;
}

int PopFront(Queue *q) {
    if (IsEmpty(q)) return -1;

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

void PushBack(Queue *q, int value) {
    QNode *node = NewNode(value);
    if (IsEmpty(q)) {
        q->head = node;
        q->tail = node;
    } else {
        q->tail->next = node;
        node->prev = q->tail;
        q->tail = node;
    }
    q->length++;
}

int PopBack(Queue *q) {
    if (IsEmpty(q)) return -1;

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

void FreeQueue(Queue *q) {
    while (!IsEmpty(q)) PopFront(q);
    free(q);
}

int main(void) {
    Queue *q = NewQueue();
    PushBack(q, 1);
    PushBack(q, 2);
    PushBack(q, 3);
    PushFront(q, 4);
    PushFront(q, 5);
    PushFront(q, 6);
    assert(PopFront(q) == 6);
    assert(PopFront(q) == 5);
    assert(PopFront(q) == 4);
    assert(PopBack(q) == 3);
    assert(PopBack(q) == 2);
    assert(PopBack(q) == 1);
    assert(IsEmpty(q));
    FreeQueue(q);
    return 0;
}
