#include <stdio.h>  // for printf

#include "skiplist.h"

int main(void) {
    Skiplist *sl = NewSkiplist();
    for (int i = 1; i < 9; i++) Put(sl, i);
    Put(sl, 3);
    Put(sl, 4);
    Put(sl, 5);
    Put(sl, 6);
    Put(sl, 7);
    Put(sl, 8);
    Print(sl);
    FreeSkiplist(sl);
    return 0;
}
