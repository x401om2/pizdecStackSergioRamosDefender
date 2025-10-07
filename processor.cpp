#include <stdio.h>
#include <math.h>
#include "stack.h"
#include "processorOperations.h"
#include "processor.h"

#define MAX_COMMANDS 300

int processingFromFile(const char* filename, processor_t* processor)
{
    FILE* file = fopen(filename, "rb");
    if (!file)
    {
        printf("не открывает дверь баран %s\n", filename);
        return 1;
    }

    printf("\nначинаем педалировать с этого письмака: %s\n", filename);
    printf("=========================================================\n");

    commandForBinary_t commands[MAX_COMMANDS] = {{CMD_NOTHING, 0, false}};                  // массив структур команд
    int count = readBinaryCommands(file, commands, MAX_COMMANDS);                           // сохр колво прочитанных команд
    fclose(file);

    int registers[4] = {0};

    executeAllCommands(commands, count, &processor -> calcStack, registers);

    stackDetor(&processor -> calcStack);
    return 0;
}

const char* getCommandName(commands_t command)          // возвр указатель на строку-константу с названием команды
{
    switch (command)
    {
        case CMD_PUSH: return "PUSH";
        case CMD_NOTHING: return "NOTHING";
        case CMD_ADD: return "ADD";
        case CMD_SUB: return "SUB";
        case CMD_MUL: return "MUL";
        case CMD_DIV: return "DIV";
        case CMD_OUT: return "OUT";
        case CMD_SQRT: return "SQRT";
        case CMD_HLT: return "HLT";
        case CMD_IN: return "IN";
        case CMD_PUSHR: return "PUSHR";
        case CMD_POPR: return "POPR";
        default: return "UNKNOWN";
    }
}

int readBinaryCommands(FILE* file, commandForBinary_t* commandList, int maxCommands)        // указ на откр бинарный файл с командами - указ на массив структур для хранения команд - макс колво команд которое можем прочитать
{
    int count = 0;                                      // счетчик прочитанных команд

    while (count < maxCommands)
    {
        int rawCommand = 0;

        if (fread(&rawCommand, sizeof(int), 1, file) != 1)                                  // читает один элемент размером int
        {
            printf("не удалось прочитать команду - readBinaryCommands\n");
            break;
        }
        commandList[count].cmd = (commands_t)rawCommand;                                    // commandList[0].cmd = (commands_t)rawCommand - (в rawCommand - мы прочитали)
        commandList[count].hasValue = false;                                                // изначально статус значения - false

        if (commandList[count].cmd == CMD_PUSH || commandList[count].cmd == CMD_PUSHR || commandList[count].cmd == CMD_POPR)
        {
            int value = 0;
            if (fread(&value, sizeof(int), 1, file) == 1)
            {
                commandList[count].value = value;                                           // как раз меняем значение value структуры commandList[0]
                commandList[count].hasValue = true;                                         // и ставим статус на true
            }
            else
            {
                printf("у команды которой должен быть аргумент - его не было - ошибка\n");
                break;
            }
        }

        count++;                                                                            // увелич колво прочитанных команд

        if (commandList[count-1].cmd == CMD_HLT)
            break;
    }
    return count;
}

void executeCommand(commandForBinary_t commandList, myStack_t* calcStack, int* registers)   // "выполнить команду" - параметр типа структуры (копия) - указатель на структуру стека - указатель на массив регистров
{
    if (commandList.cmd == CMD_PUSH && commandList.hasValue)
    {
        double value = commandList.value;
        printf("PUSH %d\n", commandList.value);
        operationsOfProcessor(CMD_PUSH, value, calcStack, registers);
    }
    else if ((commandList.cmd == CMD_PUSHR || commandList.cmd == CMD_POPR) && commandList.hasValue)
    {
        printf("%s %s\n", getCommandName(commandList.cmd), getRegisterName(commandList.value));
        operationsOfProcessor(commandList.cmd, commandList.value, calcStack, registers);
    }
    else
    {
        const char* cmdName = getCommandName(commandList.cmd);                              // указатель на неизменяемую строкуы
        printf("%s\n", cmdName);
        operationsOfProcessor(commandList.cmd, 0, calcStack, registers);                    // второй параметр 0 - тк нет доп значений у остальных команд
    }
}

void executeAllCommands(commandForBinary_t* commands, int count, myStack_t* calcStack, int* registers)      // указ на массив команд - колво команд для выполн -  - указ на массив регистров
{
    for (int i = 0; i < count; i++)
    {
        commandForBinary_t current = commands[i];                                           // создаем копию команды
        executeCommand(current, calcStack, registers);                                      // выполнение одной команды

        if (current.cmd == CMD_HLT)
        {
            break;
        }
    }
}

const char* getRegisterName(int regIndex)
{
    switch (regIndex)
    {
        case REG_RAX: return "RAX";
        case REG_RBX: return "RBX";
        case REG_RCX: return "RCX";
        case REG_RDX: return "RDX";
        default: return "UNKNOWN";
    }
}

