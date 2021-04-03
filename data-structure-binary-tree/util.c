#include "util.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/////////////////
// 整型数组 (动态内存)
/////////////////

IntArray *NewIntArray() {
    IntArray *a = malloc(sizeof(IntArray));
    a->a = malloc(32 * sizeof(int));
    a->cap = 32;
    a->n = 0;
    return a;
}

void FreeIntArray(IntArray *a) {
    if (a != NULL) {
        if (a->a != NULL) free(a->a);
        free(a);
    }
}

bool IntArrayPush(IntArray *a, int v) {
    if (a->cap < a->n + 1) {
        int cap = a->cap + 32;
        int *a1 = realloc(a->a, cap * sizeof(int));
        if (a1 == NULL) return false;
        a->a = a1;
        a->cap = cap;
    }
    a->a[a->n++] = v;
    return true;
}

int IntArraySize(IntArray *a) {
    if (a == NULL) return 0;
    return a->n;
}

int IntArrayPop(IntArray *a) {
    if (a == NULL) return -1;
    return a->a[--a->n];
}

int *IntArrayUnwrap(IntArray *a) {
    if (a == NULL) return NULL;
    return a->a;
}

/////////////////
// 动态数组 (一般类型)
/////////////////

Array *NewArray() {
    Array *a = malloc(sizeof(Array));
    a->a = malloc(32 * sizeof(void *));
    a->cap = 32;
    a->n = 0;
    return a;
}

void FreeArray(Array *a) {
    if (a != NULL) {
        if (a->a != NULL) free(a->a);
        free(a);
    }
}

bool ArrayPush(Array *a, void *v) {
    if (a->cap < a->n + 1) {
        int cap = a->cap + 32;
        void **a1 = realloc(a->a, cap * sizeof(void *));
        if (a1 == NULL) return false;
        a->a = a1;
        a->cap = cap;
    }
    a->a[a->n++] = v;
    return true;
}

int ArraySize(Array *a) {
    if (a == NULL) return 0;
    return a->n;
}

void *ArrayPop(Array *a) {
    if (a == NULL) return NULL;
    return a->a[--a->n];
}

void **ArrayUnwrap(Array *a) {
    if (a == NULL) return NULL;
    return a->a;
}

/////////////////
// 栈 (动态内存)
/////////////////

Stack *NewStack() {
    Stack *stack = malloc(sizeof(Stack));
    stack->a = NewArray();
    return stack;
}

void FreeStack(Stack *stack) {
    if (stack != NULL) {
        FreeArray(stack->a);
        free(stack);
    }
}

bool StackPush(Stack *stack, void *v) { return ArrayPush(stack->a, v); }

void *StackPop(Stack *stack) { return ArrayPop(stack->a); }

bool IsStackEmpty(Stack *stack) {
    if (stack == NULL || ArraySize(stack->a) == 0) return true;
    return false;
}

void *StackTop(Stack *stack) {
    if (IsStackEmpty(stack)) return NULL;
    void **a = ArrayUnwrap(stack->a);
    int n = ArraySize(stack->a);
    return a[n - 1];
}

/////////////////
// 队列 (动态内存)
/////////////////

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

/////////////////
// 辅助函数
/////////////////

bool IsArrayEqual(int a[], int m, int b[], int n) {
    if (m != n) return false;
    for (int i = 0; i < n; i++) {
        if (a[i] != b[i]) return false;
    }
    return true;
}

void PrintIntArray(int a[], int n) {
    printf("[");
    for (int i = 0; i < n; i++) {
        printf("%d", a[i]);
        if (i < n - 1) printf(",");
    }
    printf("]\n");
}
