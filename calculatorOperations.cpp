#include <stdio.h>
#include "stack.h"                                          // для доступа к структуре и функциям в работе со стеком
#include <math.h>
#include "calculatorOperations.h"

int operationsOfCalculator(commands command, double value, myStack_t* calcStack)
{
    switch (command)
    {
        case CMD_PUSH:
            return stackPush(calcStack, (typeOfElement)value);

        case CMD_ADD:
            return add(calcStack);

        case CMD_SUB:
            return sub(calcStack);

        case CMD_MUL:
            return mul(calcStack);

        case CMD_DIV:
            return div(calcStack);

        case CMD_OUT:
            return out(calcStack);

        case CMD_DISCRIMINANT:
            return DISCRAN(calcStack);

        case CMD_SQRT:
            return sqRT(calcStack);

        default:
            printf("ОТКУДА КОМАНДА????");
            return -1;
    }
}

int add(myStack_t* calcStack)
{
    typeOfElement val1, val2;

    if (calcStack -> size < 2)
    {
        printf("нужно 2 элемента чтобы ADD ");
        return -1;
    }
    stackPop(calcStack, &val2);
    stackPop(calcStack, &val1);

    return stackPush(calcStack, val1 + val2);
}

int sub(myStack_t* calcStack)
{
    typeOfElement val1, val2;

    if (calcStack -> size < 2)
    {
        printf("нужно 2 элемента чтобы SUB ");
        return -1;
    }
    stackPop(calcStack, &val2);
    stackPop(calcStack, &val1);
    return stackPush(calcStack, val1 - val2);
}

int DISCRAN(myStack_t* calcStack)
{
    typeOfElement a, b, c;
    typeOfElement discriminant;

    if (calcStack->size < 3)
    {
        printf("НУЖНО 3 КОЭФФИЦИЕНТА ");
        return -1;
    }
    stackPop(calcStack, &c);
    stackPop(calcStack, &b);
    stackPop(calcStack, &a);
    discriminant = b * b - 4 * a * c;
    return stackPush(calcStack, discriminant);
}

int sqRT(myStack_t* calcStack)
{
    typeOfElement sqrtValue;

    if (calcStack->size < 1)
    {
        printf("НУЖНО ЗНАЧЕНИЕ ДЛЯ КОРНЯ ");
        return -1;
    }
    stackPop(calcStack, &sqrtValue);
    if (sqrtValue < 0)
    {
        printf("отрицат не можем взять корень ");
        stackPush(calcStack, sqrtValue);
        return -1;
    }
    return stackPush(calcStack, (typeOfElement)sqrt(sqrtValue));
}

int out(myStack_t* calcStack)
{
    printf("ТЕПЕРЬ СТЕК ВОТ ТАКОЙ[%lu]: ", calcStack->size);
    for (size_t i = 0; i < calcStack->size; i++)
    {
        printf("%d ", calcStack->data[i]);
    }
    printf("\n");
    return 0;
}

int mul(myStack_t* calcStack)
{
    typeOfElement val1, val2;

    if (calcStack->size < 2)
    {
        printf("нужно 2 элемента чтобы MUL ");
        return -1;
    }
    stackPop(calcStack, &val2);
    stackPop(calcStack, &val1);
    return stackPush(calcStack, val1 * val2);
}

int div(myStack_t* calcStack)
{
    typeOfElement val1, val2;

    if (calcStack->size < 2)
    {
        printf("нужно 2 элемента чтобы DIV ");
        return -1;
    }
    stackPop(calcStack, &val2);
    if (val2 == 0)
    {
        printf("на ноль делить ПОКА НЕЛЬЗЯ БРО ");
        stackPush(calcStack, val2);
        stackPush(calcStack, 0);
        return -1;
    }
    stackPop(calcStack, &val1);
    return stackPush(calcStack, val1 / val2);
}
