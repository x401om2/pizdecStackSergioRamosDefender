#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "errorTypes.h"

errorType stackPush(myStack_t* stk, typeOfElement value)
{
    assert(stk); //пока ассерт, но надо написать верификатор eбаный
    //TODO написать реаллокацию data в случае, если переполняем массив
    //TODO написать реаллокацию data в случае, если уже слишком много свободных ячеек в массиве (мб сделать это в StackPop)

    stk -> data[stk->size++] = value;
    return ERROR_NO;
}

errorType stackPop(myStack_t* stk, typeOfElement* value)
{
    // if (stk == NULL || value == NULL)
    // {
    //     return ERROR_NULL_POINTER;
    // }

    size_t currentSize = stk->size;
    stk->size = currentSize - 1;
    *value = stk -> data[currentSize - 1];

    return ERROR_NO;
}

void printStack(myStack_t* stk)
{
    for (size_t i = 0; i < stk->size; i++)
    {
        printf("%d\n", stk->data[i]);
    }
}

int stackCtor(myStack_t* stk, size_t startingCapacity)
{
    stk -> data = (typeOfElement*) calloc(startingCapacity, sizeof(typeOfElement));
    stk -> capacity = startingCapacity;
    stk -> size = 0;

    return 0;
}

int stackDetor(myStack_t* stk)
{
    free(stk -> data);
    stk -> data = NULL;
    stk -> capacity = 0;
    stk -> size = 0;

    return 0;
}


void stackDump(myStack_t* stk, errorType err, const char* msg) // третий параметр - выводящийся текст ошибки и проверки
{
    size_t stackSize =  stk->size;
    size_t stackCapacity = stk->capacity;

#ifdef _DEBUG
    printf("stack [%p] %s (Error %d) from %s at %s %d\n", stk, msg, err, stk -> fileName, stk -> funcName, stk -> line); // %p - адрес
#else
    printf("stack [%p] %s (Error %d)\n", stk, msg, err)
#endif

    printf("    {\n");
    printf("    size = %lu\n", stackSize);
    printf("    capacity=%lu\n", stackCapacity);
    printf("    data [%p]\n", stk->data); // %p - адрес
    printf("        {\n");
    size_t i = 0;

    for (; i < stackSize; i++)
    {
        printf("        *[%lu] = %d\n", i, stk->data[i]); //если поменяем тип (ElementType), то тут вместо %d нужно будет другой спецификатор писать, что делать?
    }
    for (; i>= stackSize && i < stackCapacity; i++)
    {
        printf("         [%lu] = %d (POISON)\n", i, stk->data[i]);
    }
    printf("        }\n");
    printf("}\n");

}
