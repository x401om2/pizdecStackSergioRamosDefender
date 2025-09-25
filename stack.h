#ifndef _STACK_H_
#define _STACK_H_

#include <stdlib.h>
#include "errorTypes.h"

typedef int typeOfElement;       // если резко придется сменить тип и сделаем это в одно действие здесь

typedef struct
{
#ifdef _DEBUG                   //как компилить дебаговый режим
    const char* fileName;
    const char* funcName;
    int line;
    const char* varName;
#endif
    size_t capacity;
    size_t size;
    typeOfElement *data;

} myStack_t;

int stackCtor(myStack_t* stk, size_t startingCapacity);
int stackDetor(myStack_t* stk);

errorType stackPush(myStack_t* stk, typeOfElement value);      // errorType
errorType stackPop(myStack_t* stk, typeOfElement* value);

//stack Verification , errorParse

void stackDump(myStack_t* stk, errorType err, const char* msg);

void printStack(myStack_t* stk);

#endif
