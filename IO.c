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

// Checks if the set of tokens has IO (> or <) in it
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

// Checks if the set of tokens has a valid input redirection
// returns inputfile (null if there is no inputfile)
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

// Checks if the set of tokens has a valid input redirection
// returns inputfile (null if there is no inputfile)
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

// Gets the complete command given a tokenlist
void getCommandIO(tokenlist* command, tokenlist *tokens)
{
    if (tokens->size > 0)
    {
        for(int i = 0; i < tokens->size; i++)
        {
            if(strcmp(tokens->items[i], ">") == 0 || strcmp(tokens->items[i], "<") == 0)
            {
                break;
            }
            else
            {
                add_token(command, tokens->items[i]);
            }
        }
    }
}

// Does all the redirection
void redirection(tokenlist *tokens)
{
    int valid = isValid(tokens);

    if (valid == 1)
    {

        char *inputFile = isValidInputRedir(tokens);
        char *outputFile = isValidOutputRedir(tokens);

        tokenlist *command = new_tokenlist();

        getCommandIO(command, tokens);

        // If we need to perform both input and output redirection
        if (inputFile != NULL && outputFile != NULL)
        {
            IORedirection(command, inputFile, outputFile);
        }

        // else if we only need to do output redirection
        else if (inputFile == NULL && outputFile != NULL)
        {
            outputRedirection(command, outputFile);
        }

        // if we only need to perform input redirection
        else if (outputFile == NULL && inputFile != NULL)
        {
            inputRedirection(command, inputFile);
        }

    }
}

// Does input redirection
void inputRedirection(tokenlist *command, char *inputFile)
{

    int fd; // stores the file id
    int ret;

    // open the file with Read Only flag
    fd = open(inputFile, O_RDONLY);

    // fork
    pid_t pid = fork();


    if(pid == 0)
    {
        // Child process
        if (fd < 0)
        {
            printf("FILE DOES NOT EXIST!!!\n");
            printf("please enter a valid file\n");
            exit(0);

        }

        // redirect the file despritor
        ret = dup2(fd, STDIN_FILENO);

        // if we have an error we quit
        if (ret < 0)
        {
            exit(0);
        }

        // close the file descriptor
        close(fd);

        // exectue the command
        commandExecution(command);

        // exit afterwards
        exit(0);
    }
    else
    {
        // Wait till the child process is finished
        waitpid(pid,NULL,0);
        // close the file descriptor
        close(fd);

    }
}
// Does output redirection
void outputRedirection(tokenlist *command, char *outputFile)
{

    int fd; // stores the file id
    int ret;


    // open the file
    // if it does not exist we create a file
    fd = open(outputFile, O_CREAT | O_RDWR | O_TRUNC, 0777);

    // fork
    pid_t pid = fork();

    if(pid == 0)
    {
        // Child process
        if (fd < 0)
        {
            printf("ERROR fd file\n");
            exit(0);
        }

        // redirect the file despritor
        ret = dup2(fd, STDOUT_FILENO);

        // if we have an error we quit
        if (ret < 0)
        {
            printf("ERROR ret file\n");
        }

        // close the desriptor
        close(fd);

        // execute the command
        commandExecution(command);

        // exit
        exit(0);

    }
    else
    {
        // wait till childs process is done
        waitpid(pid,NULL,0);
        close(fd);
    }
}
// IO redirection for both input and output redirecton
void IORedirection(tokenlist *command, char *inputFile, char *outputFile)
{

    int fd1, fd2; // fd1 is for output file // fd2 output file
    int ret1, ret2;


    fd1 = open(outputFile, O_CREAT | O_RDWR | O_TRUNC, 0777);
    fd2 = open(inputFile, O_RDONLY);

    pid_t pid = fork();

    if(pid == 0)
    {

        if (fd1 < 0)
        {
            printf("Error with fd 1 output file\n");
        }
        if (fd2 < 0)
        {
            printf("FILE DOES NOT EXIST!!!\n");
            printf("please enter a valid file\n");
        }


        // redirect the filedescriptors
        ret1 = dup2(fd1, STDOUT_FILENO);
        ret2 = dup2(fd2, STDIN_FILENO);

        // if we have an errroe we print them
        if (ret1 < 0)
        {
            printf("ERROR\n");
            exit(0);
        }
        if (ret2 < 0)
        {
            printf("Error\n");
            exit(0);
        }

        // close the file desriptors
        close(fd1);
        close(fd2);

        // execute the command
        commandExecution(command);
        exit(0);

    }
    else
    {
        // wait till child process is done
        waitpid(pid,NULL,0);
        close(fd1);
        close(fd2);
    }
}

        // Then >
    }
}
