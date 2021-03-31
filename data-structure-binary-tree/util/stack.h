// 辅助数据结构 - 栈

#include <stdbool.h>

// 栈
typedef struct _Stack {
    void **a;
    int len;
    int cap;
} Stack;

Stack *NewStack();
void FreeStack(Stack *stack);
bool StackPush(Stack *stack, void *v);
void *StackPop(Stack *stack);
bool IsStackEmpty(Stack *stack);
