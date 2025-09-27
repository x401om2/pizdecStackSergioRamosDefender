#include <stdio.h>
#include "testingStack.h"
#include "stack.h"
#include "errorTypes.h"

void testForFullStack(myStack_t* stack)
{
    int value = 0;
    for (int i = 0; i < 2; i++)
    {
        errorType result = stackPush(stack, 20);
        errorType err = stackVerificator(stack);
        if (result != ERROR_NO)
        {
            stackDump(stack, result, "STACK FULL - NO ELEMENTS ADDED");
            break;
        }
        stackDump(stack, err, "ADDING AN ELEMENT");
    }
}

void testForEmptyStack(myStack_t* stack)
{
    for (int i = 0; i < stack -> capacity; i++)
    {
        int value = 0;
        errorType result = stackPop(stack, &value);
        errorType err = stackVerificator(stack);

        if (result != ERROR_NO)
        {
            stackDump(stack, result, "СТЕК ПУСТОЙ - нет элементов");
            break;
        }
        stackDump(stack, err, "УДАЛЕНИЕ ЭЛЕМЕНТА");
    }
}

void funcSwitchErrors(errorType err) // for add cases if we need it
{
    switch(err) {
        case ERROR_NO:
            printf("stack status: OK\n");
            break;

        case EMPTY_STACK:
            printf("stack status: stack is empty\n");
            break;

        case NULL_POINTER_STACK:
            printf("stack status: null pointer to stack structure\n");
            break;

        case NULL_DATA_POINTER:
            printf("stack status: null pointer to stack data\n");
            break;

        case BAD_SIZE:
            printf("stack status: invalid size\n");
            break;

        case BAD_CAPACITY:
            printf("stack status: invalid stack capacity\n");
            break;

        case STACK_NO_MEMORY:
            printf("stack status: memory was not allocated\n");
            break;

        case SIZE_BIGGER_THAN_CAPACITY:
            printf("Stack status: size greater than capacity - incorrect\n");
            break;

        default:
            printf("статус стека: неизвестная ошибка\n");
            break;
    }
}

void allTestsForBitches()
{
    myStack_t* testStackOne = NULL;
    myStack_t stk = {};

    size_t testCapacityZero = 0;
    size_t testCapacity = 2;

    printf("\n|==================TEST OF ZERO CAPACITY==================|\n");
    errorType firstBlood = stackCtor(&stk, testCapacityZero);
    stackDump(&stk, firstBlood, "FIRST BROO");

    printf("\n|==================TEST OF NULL POINTER STACK==================|\n");
    errorType secondBlood = stackCtor(testStackOne, 0);
    stackDump(testStackOne, secondBlood, "SECOND BROO");

    printf("\n|==================TEST OF NULL DATA POINTER==================|\n");
    errorType thirdBlood = stackCtor(&stk, testCapacity);
    stk.data = NULL;
    errorType dataError = stackVerificator(&stk);
    stackDump(&stk, dataError, "THIRD BROO");

}

void simpleTestForFullAndEmptyStack()
{
    myStack_t stack = {};

    stackCtor(&stack, 3);
    stackPush(&stack, 10);
    stackPush(&stack, 20);

    stackDump(&stack, ERROR_NO, "AFTER ADD 2 ELEMENTS");


    testForFullStack(&stack);
    testForEmptyStack(&stack);


    stackPush(&stack, 11001);
    stackDump(&stack, ERROR_NO, "END OF TESTS");

    stackDetor(&stack);
}
