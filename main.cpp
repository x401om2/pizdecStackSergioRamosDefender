#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "testingStack.h"

// poison - отдельное значение конкретное число(в 16 ричном представлении буквы) и в POP тоже остается poison +

// в push - сразу проверка и реаллоцирование памяти если size == capacity +

//TODO файлик cpp со своими классными функциями полезными чтобы реюзить

int main() {

    myStack_t stack = {0};
    typeOfElement value = 0;
    errorType result = ERROR_NO;

    allTestsForBitches();

    simpleTestForFullAndEmptyStack();

    return 0;
}
