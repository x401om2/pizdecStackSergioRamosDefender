#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "testingStack.h"
#include "calculator.h"
#include "calculatorOperations.h"

//TODO poison - отдельное значение конкретное число(в 16 ричном представлении буквы) и в POP тоже остается poison +

//TODO в push - сразу проверка и реаллоцирование памяти если size == capacity +

//TODO файлик cpp со своими классными функциями полезными чтобы реюзить

int main() {
    myStack_t calcStack;

    errorType resultOfCtor = stackCtor(&calcStack, 10);

    // allTestsForBitches();
    // simpleTestForFullAndEmptyStack();

    translator();
    calculateFromFile("processor.bin", &calcStack);
    return 0;
}
