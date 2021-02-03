// Comment test

#include "IO.h"
#include "tokenlist.h"
#include "CommandExe.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

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

char *isValidInputRedir(tokenlist *tokens)
{
    char *inputFile = NULL;

    for (int i = 0; i < tokens->size; i++)
    {
        if (strcmp(tokens->items[i], "<") == 0)
        {
            if (i + 1 < tokens->size)
            {
                inputFile = tokens->items[i + 1];
                return inputFile;
            }
        }
    }
    return inputFile;
}

char *isValidOutputRedir(tokenlist *tokens)
{

    char *outputFile = NULL;

    for (int i = 0; i < tokens->size; i++)
    {
        if (strcmp(tokens->items[i], ">") == 0)
        {
            if (i + 1 < tokens->size)
            {
                outputFile = tokens->items[i + 1];
                return outputFile;
            }
        }
    }
    return outputFile;
}

char *getCommand(tokenlist *tokens)
{
    char *command = NULL;
    if (tokens->size > 0)
    {
        command = tokens->items[0];
        return command;
    }
    return command;
}

void redirection(tokenlist *tokens)
{
    int valid = isValid(tokens);

    if (valid == 1)
    {

        char *inputFile = isValidInputRedir(tokens);
        char *outputFile = isValidOutputRedir(tokens);

        tokenlist *command = new_tokenlist();
        add_token(command, getCommand(tokens));

        pid_t pid = fork();

        if (pid == 0)
        {
            // child process

            if (inputFile != NULL && outputFile != NULL)
            {
                printf("IO redirection\n");
                IORedirection(command, inputFile, outputFile);
            }
            else if (inputFile != NULL && outputFile == NULL)
            {
                printf("Output redirection\n");
                inputRedirection(command, outputFile);
            }
            else if (outputFile != NULL && inputFile == NULL)
            {
                printf("Input redirection\n");
                outputRedirection(command, inputFile);
            }
        }
    }
}

void inputRedirection(tokenlist *command, char *inputFile)
{
    int fd;
    int ret;
    fd = open(inputFile, O_RDONLY);

    if (fd < 0)
    {
        printf("ERROR file\n");
    }

    ret = dup2(fd, STDIN_FILENO);

    if (ret < 0)
    {
        printf("ERROR file\n");
    }

    commandExecution(command);

    close(fd);
}

void outputRedirection(tokenlist *command, char *outputFile)
{
    int fd;
    int ret;
    fd = open(outputFile, O_CREAT | O_WRONLY);

    if (fd < 0)
    {
        printf("ERROR file\n");
    }

    ret = dup2(fd, STDOUT_FILENO);
    if (ret < 0)
    {
        printf("ERROR file\n");
    }

    commandExecution(command);

    close(fd);
}

void IORedirection(tokenlist *command, char *inputFile, char *outputFile)
{
    int fd1, fd2;
    int ret1, ret2;

    fd1 = open(outputFile, O_CREAT | O_WRONLY);
    fd2 = open(inputFile, O_RDONLY);

    if (fd1 < 0)
    {
        printf("Error with output file\n");
    }
    if (fd2 < 0)
    {
        printf("Error with input file\n");
    }

    ret1 = dup2(fd1, STDOUT_FILENO);
    ret2 = dup2(fd2, STDIN_FILENO);

    if (ret1 < 0)
    {
        printf("ERROR file\n");
    }
    if (ret2 < 0)
    {
        printf("Error inputfile\n");
    }

    commandExecution(command);

    close(fd1);
    close(fd2);
}