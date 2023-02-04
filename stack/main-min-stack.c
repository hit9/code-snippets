// 数据结构 - 最小栈 - 在栈的基础上，实现一个常数时间的最小值函数
// https://writings.sh/post/monotonous-stack-and-monotonous-queue
// https://leetcode-cn.com/problems/min-stack/
// 要求 Push() Pop() Min() 三个函数平均时间复杂度 O(1)

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>  // for malloc, free

// 思路：
// 两个栈实现
// 一个栈 a 是先进后出栈
// 一个是 b 单调递减栈
// 此文件只需看 Push 和 Pop 函数的而实现，其他都是辅助函数。

////////
// 声明
////////

// 动态内存版栈实现
typedef struct {
    int *a;
    int len;
    int cap;
} Stack;

// 最小栈
typedef struct {
    Stack *a;
    Stack *b;
} MinStack;

Stack *NewStack();
void FreeStack(Stack *stack);
bool StackPush(Stack *stack, int value);
int StackPop(Stack *stack);
int StackTop(Stack *stack);
int StackLen(Stack *Stack);

MinStack *NewMinStack();
void FreeMinStack(MinStack *m);
bool Push(MinStack *m, int value);
int Pop(MinStack *m);
int Min(MinStack *m);

/////////////
// 实现最小栈
////////////

MinStack *NewMinStack() {
    MinStack *m = malloc(sizeof(MinStack));
    m->a = NewStack();
    m->b = NewStack();
    return m;
}

void FreeMinStack(MinStack *m) {
    FreeStack(m->a);
    FreeStack(m->b);
    free(m);
}

bool Push(MinStack *m, int value) {
    // 只有不大于 b 的栈顶时，才入栈 b
    if (StackLen(m->b) == 0 || value <= StackTop(m->b)) StackPush(m->b, value);
    return StackPush(m->a, value);
}

int Pop(MinStack *m) {
    if (StackLen(m->a) == 0) return -1;
    int value = StackPop(m->a);
    // 只有等于 b 的栈顶时，才出栈 b
    if (value == StackTop(m->b)) StackPop(m->b);
    return value;
}

int Min(MinStack *m) {
    if (StackLen(m->a) == 0) return -1;
    return StackTop(m->b);
}

//////////////////
// 实现栈 （辅助）
/////////////////

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

bool StackPush(Stack *stack, int value) {
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

int StackPop(Stack *stack) {
    if (stack->len == 0) return -1;
    return stack->a[--stack->len];
}

int StackTop(Stack *stack) {
    if (stack->len == 0) return -1;
    return stack->a[stack->len - 1];
}

int StackLen(Stack *stack) { return stack->len; }

////////
// 测试
////////

int main(void) {
    MinStack *m = NewMinStack();
    Push(m, 3);
    Push(m, 2);
    Push(m, 5);
    Push(m, 1);
    assert(Min(m) == 1);
    assert(Pop(m) == 1);
    assert(Min(m) == 2);
    assert(Pop(m) == 5);
    assert(Min(m) == 2);
    return 0;
}
