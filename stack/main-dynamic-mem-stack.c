// 栈（动态内存版）

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>  // for malloc, free

typedef struct {
    int *a;
    int len;
    int cap;
} Stack;

Stack *NewStack() {
    Stack *stack = malloc(sizeof(Stack));
    stack->a = malloc(32 * sizeof(int));
    stack->cap = 32;
    stack->len = 0;
    return stack;
}

void FreeStack(Stack *stack) {
    free(stack->a);
    free(stack);
}

bool Push(Stack *stack, int value) {
    // 如果需要重新申请内存
    if (stack->cap < stack->len + 1) {
        int cap = stack->cap + 32;
        int *a = realloc(stack->a, cap * sizeof(int));
        if (a == NULL) {
            return false;
        }
        stack->a = a;
        stack->cap = cap;
    }

    stack->a[stack->len++] = value;
    return true;
}

int Pop(Stack *stack) {
    if (stack->len == 0) return -1;
    return stack->a[--stack->len];
}

int main(void) {
    Stack *stack = NewStack();
    Push(stack, 1);
    Push(stack, 2);
    Push(stack, 3);
    assert(Pop(stack) == 3);
    assert(Pop(stack) == 2);
    assert(Pop(stack) == 1);
    assert(Pop(stack) == -1);
    FreeStack(stack);
    return 0;
}
