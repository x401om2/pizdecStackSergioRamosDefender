#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

#define INIT(name) myStack_t name = {__FILE__, __func__, __LINE__, #name, NULL, 0, 0}

int main() {
#ifdef _DEBUG
    INIT(stk1);
#else
    myStack_t stk1 = {};
#endif
    typeOfElement x = 0;        // Объявлена переменная x
    errorType result = ERROR_NO;

    stackCtor(&stk1 , 5);
    printf("%p, %lu, %lu\n", stk1.data, stk1.size, stk1.capacity);


    stackPush(&stk1, 10);
    stackPush(&stk1, 20);
    stackPush(&stk1, 30);

    stackDump(&stk1, ERROR_NO, "stack after creation");

    result = stackPop(&stk1, &x);

    if (result == ERROR_NO) {
        printf("popped value: %d\n", x);
    }

    printStack(&stk1);

    stackDetor(&stk1);

    return 0;
}
