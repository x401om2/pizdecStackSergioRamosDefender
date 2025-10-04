#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "stack.h"
#include "calculatorOperations.h"

#define EBANUTAYA_DLINA_TAKOY_NET 100

int calculateFromFile(const char* filename, myStack_t* calcStack)
{
    FILE* file = fopen(filename, "rb");

    if (!file) {
        printf("Error: Cannot open file %s\n", filename);
        return 1;
    }

    int command = 0;                                                // для хранения кода команды
    int numberOfLine = 0;                                           // порядковый номер текущей строки
    double value = 0;                                               // для хранения аргумента команды PUSH

    printf("\nначинаем педалировать с этого письмака: %s\n", filename);
    printf("----------------------------\n");


    while (fread(&command, sizeof(int), 1, file) == 1)
    {
        numberOfLine++;

        if (command == CMD_PUSH)
        {

            if (fread(&value, sizeof(double), 1, file) != 1)
            {
                printf("Ошибка чтения значения для PUSH на команде №%d\n", numberOfLine);
                break;
            }
            printf("Команда %d: PUSH %.0f\n", numberOfLine, value);
            int result = operationsOfCalculator((commands)command, value, calcStack);

        } else {

            // Получаем имя команды для отладки
            const char* cmdName = "UNKNOWN";
            switch (command) {
                case CMD_ADD:
                    cmdName = "ADD";
                    break;
                case CMD_SUB:
                    cmdName = "SUB";
                    break;
                case CMD_MUL:
                    cmdName = "MUL";
                    break;
                case CMD_DIV:
                    cmdName = "DIV";
                    break;
                case CMD_OUT:
                    cmdName = "OUT";
                    break;
                case CMD_SQRT:
                    cmdName = "SQRT";
                    break;
                case CMD_DISCRIMINANT:
                    cmdName = "DISCRIMINANT";
                    break;
            }
            printf("Команда %d: %s\n", numberOfLine, cmdName);
            int result = operationsOfCalculator((commands)command, 0, calcStack);

        }

        if (command == CMD_OUT)
        {
            out(calcStack);
        }
    }

    if (calcStack -> size > 0)
    {
        typeOfElement resultValue;
        stackPop(calcStack, &resultValue);
        printf("\nПОЩИТАЛИ: %d\n", resultValue);

    } else {
        printf("\nНЕТУ РУЧЕК(ЭЛЕМЕНТА) - НЕТ КОНФЕТКИ(РЕЗУЛЬТАТА)\n");
    }

    fclose(file);
    stackDetor(calcStack);

    return 0;
}


// void readFromFuckingSlaveNiggersFile
