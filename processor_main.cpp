#include <stdio.h>
#include <math.h>
#include <stack.h>
#include <processorOperations.h>
#include "processor.h"

int main()
{
    processor_t cpu;

    processorCtor(&cpu);
    processorDump(&cpu, "Создан");

    myStack_t calcStack;
    stackCtor(&calcStack, 20);
    processingFromFile("processor.bin", &cpu);

    return 0;
}
