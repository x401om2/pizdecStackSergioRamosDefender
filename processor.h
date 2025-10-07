#ifndef CALCULATOR_H_
#define CALCULATOR_H_

#include "stack.h"

int processingFromFile(const char* filename, processor_t* processor);

int readBinaryCommands(FILE* file, commandForBinary_t* commands, int maxCommands);
void executeCommand(commandForBinary_t command, myStack_t* calcStack, int* registers);
void executeAllCommands(commandForBinary_t* commands, int count, myStack_t* calcStack, int* registers);
const char* getCommandName(commands_t command);

const char* getRegisterName(int regIndex);
// void processorDetor(processor_t* processor);
// int processorCtor(processor_t* processor, int stackSize, int codeSize);

#endif
