#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "errorTypes.h"
#include "stack.h"
#include "testingStack.h"

#define STACK_CHECK_AND_RETURN(stk) \
    do { \
        errorType resultOfCheck = stackVerificator(stk); \
        if (resultOfCheck != ERROR_NO) { \
            return resultOfCheck; \
        } \
    } while(0)


// задефайнить проверку стека ВЕЗДЕ и внести проверку s > c добавить просто реаллокацию +
//TODO ассерты закинуть

errorType stackPush(myStack_t* stk, typeOfElement value)
{
    STACK_CHECK_AND_RETURN(stk);

    if (stk -> size == stk -> capacity)
    {
        errorType resultOfRealloc = reallocStack(stk);
        if (resultOfRealloc != ERROR_NO)
        {
            return resultOfRealloc;
        }
    }

    stk -> data[stk -> size] = value;
    (stk -> size)++;

    return ERROR_NO;
}

errorType stackPop(myStack_t* stk, typeOfElement* value)
{
    STACK_CHECK_AND_RETURN(stk);

    if (stk -> size == 0)
    {
        return EMPTY_STACK;
    }

    stk -> size--;
    *value = stk -> data[stk -> size];
    stk -> data[stk -> size] = POISON;

    return ERROR_NO;
}

//TODO канарейка вначале и в конце
errorType stackCtor(myStack_t* stk, size_t startingCapacity)
{
    if (stk == NULL)
        return NULL_POINTER_STACK;

    if (startingCapacity <= 0)
        return BAD_CAPACITY;

    stk -> data = (typeOfElement*) calloc(startingCapacity, sizeof(typeOfElement));

    if (stk -> data == NULL)
        return NULL_DATA_POINTER;

    for (size_t i = 0; i < startingCapacity; i++)
    {
        stk -> data[i] = POISON;
    }

    stk -> capacity = startingCapacity;
    stk -> size = 0;

    return ERROR_NO;
}

errorType stackDetor(myStack_t* stk)
{
    if (stk == NULL)
        return NULL_POINTER_STACK;

    free(stk -> data);

    stk -> data = NULL;
    stk -> capacity = 0;
    stk -> size = 0;

    return ERROR_NO;
}

errorType stackDump(myStack_t* stk, errorType err, const char* msg) // третий параметр - выводящийся текст ошибки и проверки
{
    printf("\n--------------------------------THE NEW DUMPY BITCHES--------------------------------\n");
    printf("\nMessage: %s\n", msg);
    printf("Error code: %d\n", err);
    printf("Stack address: %p\n", stk);

    if (stk == NULL)
    {
        printf("\n--------------------------------THE END DUMPY BITCHES--------------------------------\n");
        return NULL_POINTER_STACK;
    }
    size_t stackSize =  stk -> size;
    size_t stackCapacity = stk -> capacity;

    funcSwitchErrors(err); // print stack status

    printf("size: %lu\n", stk -> size);
    printf("capacity: %lu\n", stk -> capacity);
    printf("data pointer: %p\n", stk -> data);

    stackVerificator(stk);

    if(stk -> data != NULL && stk -> capacity > 0 && stk -> size >= 0)
    {
        printf("Data contents:\n");
        for(size_t i = 0; i < stk -> capacity; i++)
        {
            if(i < stk -> size)
            {
                printf("  *[%lu] = %d (active)\n", i, stk -> data[i]);
            } else {
                printf("  [%lu] = %X (POISON)\n", i, stk -> data[i]);
            }
        }
    }
    printf("\n--------------------------------THE END DUMPY BITCHES--------------------------------\n");
    return ERROR_NO;
}

errorType stackVerificator(myStack_t* stk)
{
    if (stk == NULL)
    {
        return NULL_POINTER_STACK;
    }
    if (stk -> size < 0)
    {
        return BAD_SIZE;
    }
    if (stk -> data == NULL)
    {
        return NULL_DATA_POINTER;
    }
    if (stk -> capacity <= 0)
    {
        return BAD_CAPACITY;
    }
    if (stk -> size > stk -> capacity)
    {
        return SIZE_BIGGER_THAN_CAPACITY;
    }
    return ERROR_NO;
}

errorType reallocStack(myStack_t* stk)
{
    size_t newCapacity = (stk -> capacity) * INCREASE_CAPACITY;

    typeOfElement* newData = (typeOfElement*) realloc(stk -> data, newCapacity * sizeof(typeOfElement));

    stk -> data = newData;

    for (size_t i = stk -> capacity; i < newCapacity; i++)
    {
        stk -> data[i] = POISON;
    }

    stk -> capacity = newCapacity;

    return ERROR_NO;
}
