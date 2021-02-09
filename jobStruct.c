//Project 1
//COP4610
//Venkata Sai Pavan Kumar Vadrevu, Daniel Jamsheedy, Luke Power

#include "jobStruct.h"
#include <strings.h>
#include <unistd.h>
#include <stdio.h>

jobStruct* copyJob(jobStruct* job)
{
    jobStruct* result = newJob();
    result->cmdNum = job->cmdNum;
    result->pid = job->pid;
    result->command = new_tokenlist();
    result->completed = job->completed;
    result->timeTaken = job->timeTaken;
    result->startTime = job->startTime;
    result->endTime = job->endTime;
    for (int i = 0; i < (job->command)->size; i++)
    {
        add_token(result->command, (job->command)->items[i]);
    }
    return result;
}

jobStruct* newJob(void)
{
    jobStruct* job = (jobStruct *)malloc(sizeof(jobStruct));

    job->cmdNum = -1;
    job->pid = -1;
    job->command = NULL;
    job->completed = 0;
    job->timeTaken = 0;
    job->startTime = 0;
    job->endTime = 0;
    return job;
}

jobStruct* makejob(int cmdNum, pid_t pid, tokenlist* tokens)
{
    jobStruct* job = newJob();

    if(job == NULL)
    {
        job = newJob();
    }

    job->cmdNum = cmdNum;
    job->pid = pid;
    job->completed = 0;

    job->startTime = 0;
    job->endTime = 0;

    job->command = new_tokenlist();
    job->timeTaken = 0;
    for (int i = 0; i < tokens->size; i++)
    {
        add_token(job->command, tokens->items[i]);
    }

    return job;
}

char* getCommandJob(tokenlist* tokens)
{
    int size = 0;

    for(int i = 0; i < tokens->size; i++)
    {
        size += strlen(tokens->items[i]) + 1;
    }

    char* name = (char* ) malloc(size);
    strcpy(name, "");
    for(int i = 0; i < tokens->size; i++)
    {
        strcat(name, tokens->items[i]);
        if( i != tokens->size - 1)
            strcat(name , " ");
    }

    return name;
}
void printDone(jobStruct* job)
{
    char* name = getCommandJob(job->command);
    printf("[%d]+ [%ld] [%s]\n", job->cmdNum, (long)job->pid, name);

    free(name);
    name = NULL;
}
void printJob(jobStruct* job)
{

    if(job == NULL)
    {
        printf("NULL JOB\n");
    }
    else{
        char* name = getCommandJob(job->command);

        printf("[%d]+ [%ld] [%s]\n", job->cmdNum, (long)job->pid, name);
            free(name);
    name = NULL;
    }
}

void freeJob(jobStruct* job)
{

    if(job == NULL)
    {
        return;
    }
    if(job != NULL){

        free(job);
        job = NULL;
    }
}
