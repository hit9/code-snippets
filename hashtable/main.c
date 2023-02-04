// cc main.c hashtable.c
// ./a.out

#include <assert.h>  // for assert
#include <stdio.h>   // for printf

#include "hashtable.h"

int main(void) {
    // 初始化
    int n1 = 13;
    T m1[n1];
    Init(m1, n1);

    // 插入和查询
    int k1 = 172;
    int v1 = 123;
    Set(m1, n1, k1, v1);

    assert(Has(m1, n1, k1) == true);      // 存在
    assert(Has(m1, n1, 15738) == false);  // 不存在

    assert(Get(m1, n1, k1, 0) == v1);    // 存在
    assert(Get(m1, n1, 15738, 0) == 0);  // 不存在

    // 扩展
    int n2 = n1 + n1;
    T m2[n2];
    Copy(m1, n1, m2, n2);

    assert(Get(m2, n2, k1, 0) == v1);  // 数据已迁移

    // 删除
    assert(Pop(m2, n2, k1, 0) == v1);  // 存在
    assert(Pop(m2, n2, k1, 0) == 0);   // 已不存在

    // 打印
    Set(m2, n2, 123, 132);
    Set(m2, n2, 678, 687);
    Set(m2, n2, 456, 465);
    Set(m2, n2, 789, 798);

    for (int i = 0; i < n2; i++) {
        if (m2[i].used) {
            int k = m2[i].k;
            int v = m2[i].v;
            printf("%d => %d \n", k, v);
        }
    }

    return 0;
}
