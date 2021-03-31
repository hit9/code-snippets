// 辅助数据结构 - 栈

#include "stack.h"

#include <stdbool.h>
#include <stdlib.h>

Stack *NewStack() {
    Stack *stack = malloc(sizeof(Stack));
    stack->a = malloc(32 * sizeof(void *));
    stack->cap = 32;
    stack->len = 0;
    return stack;
}

void FreeStack(Stack *stack) {
    free(stack->a);
    free(stack);
}

bool Push(Stack *stack, void *v) {
    // 如果需要重新申请内存
    if (stack->cap < stack->len + 1) {
        int cap = stack->cap + 32;
        void **a = realloc(stack->a, cap * sizeof(void *));
        if (a == NULL) {
            return false;
        }
        stack->a = a;
        stack->cap = cap;
    }

    stack->a[stack->len++] = v;
    return true;
}

void *Pop(Stack *stack) {
    if (stack->len == 0) return NULL;
    return stack->a[--stack->len];
}

bool IsEmpty(Stack *stack) {
    if (stack == NULL || stack->len == 0) return true;
    return false;
}
