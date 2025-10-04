#include <stdio.h>
#include <string.h>
#include "calculatorOperations.h"

int translator()
{
    FILE* assemblya = fopen("assembler.txt", "r");
    FILE* processor = fopen("processor.bin", "wb");

    char command[20];
    double number = 0;

    while (fscanf(assemblya, "%s", command) != EOF)
    {
        if (strcmp(command, "push") == 0)
        {
            fscanf(assemblya, "%lf", &number);
            int command_code = CMD_PUSH;

            fwrite(&command_code, sizeof(int), 1, processor);
            fwrite(&number, sizeof(double), 1, processor);

        }
        else if (strcmp(command, "add") == 0)
        {
            int command_code = CMD_ADD;
            fwrite(&command_code, sizeof(int), 1, processor);
        }
        else if (strcmp(command, "sub") == 0)
        {
            int command_code = CMD_SUB;
            fwrite(&command_code, sizeof(int), 1, processor);
        }
        else if (strcmp(command, "mul") == 0)
        {
            int command_code = CMD_MUL;
            fwrite(&command_code, sizeof(int), 1, processor);
        }
        else if (strcmp(command, "div") == 0)
        {
            int command_code = CMD_DIV;
            fwrite(&command_code, sizeof(int), 1, processor);
        }
        else if (strcmp(command, "out") == 0)
        {
            int command_code = CMD_OUT;
            fwrite(&command_code, sizeof(int), 1, processor);
        }
        else if (strcmp(command, "sqrt") == 0)
        {
            int command_code = CMD_SQRT;
            fwrite(&command_code, sizeof(int), 1, processor);
        }
        else if (strcmp(command, "discriminant") == 0)
        {
            int command_code = CMD_DISCRIMINANT;
            fwrite(&command_code, sizeof(int), 1, processor);
        }
    }

    fclose(assemblya);
    fclose(processor);
    printf("БИНАРНИК ЗЛОЕБУЧ\n");

    return 0;
}
