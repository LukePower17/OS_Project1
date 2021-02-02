#include "IO.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int isValid(tokenlist *tokens)
{
    for (int i = 0; i < tokens->size; i++)
    {
        if ((strcmp(tokens->items[i], ">") == 0) || (strcmp(tokens->items[i], "<") == 0))
        {
            return 1;
        }
    }

    return 0;
}

void redirection(tokenlist *tokens)
{

    int value = isValid(tokens);

    if (value == 1)
    {
        int inputRedir, outputRedir;
        inputRedir = outputRedir = 0;

        char *inputFile;
        char *outputFile;
        char *command;

        command = inputFile = outputFile = NULL;

        for (int i = 0; i < tokens->size; i++)
        {
            if (i == 0)
            {
                command = tokens->items[i];
            }
            if (strcmp(tokens->items[i], "<") == 0)
            {
                inputRedir += 1;

                i++;
                if (i < tokens->size)
                {
                    inputFile = tokens->items[i];
                }
                else
                {
                    return;
                }
            }
            else if (strcmp(tokens->items[i], ">") == 0)
            {
                outputRedir += 1;

                i++;
                if (i < tokens->size)
                {
                    outputFile = tokens->items[i];
                }
                else
                {
                    return;
                }
            }
        }

        tokenlist *commandList = new_tokenlist();
        add_token(commandList, command);

        // Then we have redirection
        int dup(int fd);

        // First priority is for < operator
        if (inputRedir == 0 && outputRedir == 1)
        {
            int fd = open(outputFile, O_RDWR | O_CREAT | O_TRUNC);

            pid_t p_id = fork();

            if (p_id == 0)
            {
                close(1);

                dup(fd);
                close(fd);

                // Execute the commaand
                commandExecution(commandList);
            }
            else
            {
                close(fd);
                // wait for p_id
            }
        }
        else if (inputRedir == 1 && outputRedir == 1)
        {
            int fd = open(inputFile, O_RDONLY);

            if (fd < 0)
            {
                printf("Error the inputfile cannot be read");
                exit(0);
            }
            pid_t p_id = fork();
            // Closing stdin

            if (p_id == 0)
            {
                close(0);
                dup(fd);
                close(fd);

                // Execute the commaand
                // execv(command);
                int fd2 = open(outputFile, O_RDWR | O_CREAT | O_TRUNC);

                pid_t p_id2 = fork();

                if (p_id2 == 0)
                {
                    close(1);

                    dup(fd2);
                    close(fd2);

                    // Execute the commaand
                    commandExecution(commandList);

                    // execv("/bin", command);
                }
                else
                {
                    close(fd2);
                    // wait for p_id
                }
            }
            else
            {
                close(fd);
                // wait for p_id
            }
        }

        else if (inputRedir == 1 && outputRedir == 0)
        {
            int fd = open(inputFile, O_RDONLY);

            if (fd < 0)
            {
                printf("Error the inputfile cannot be read");
                exit(0);
            }
            pid_t p_id = fork();
            // Closing stdin

            if (p_id == 0)
            {
                close(0);
                dup(fd);
                close(fd);

                // Execute the commaand
                commandExecution(commandList);
            }
            else
            {
                close(fd);
                // wait for p_id
            }
        }

        // Then >
    }
}
