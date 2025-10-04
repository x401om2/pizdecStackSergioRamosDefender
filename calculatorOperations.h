#ifndef CALCULATOR_OPERATIONS_H_
#define CALCULATOR_OPERATIONS_H_
#include "stack.h"


typedef enum
{
    CMD_NOTHING = 0,
    CMD_PUSH = 1,   // добавить в стек
    CMD_ADD = 3,    // сложить
    CMD_SUB = 4,    // вычитание
    CMD_MUL = 5,    // умножение
    CMD_DIV = 6,    // деление
    CMD_OUT = 7,    // вывод результата
    CMD_SQRT = 8,   // корень
    CMD_DISCRIMINANT = 9 // дискр

} commands;


int operationsOfCalculator(commands command, double value, myStack_t* calcStack);

int add(myStack_t* calcStack);
int sub(myStack_t* calcStack);
int div(myStack_t* calcStack);
int mul(myStack_t* calcStack);

int out(myStack_t* calcStack);

int DISCRAN(myStack_t* calcStack);
int sqRT(myStack_t* calcStack);

#endif
