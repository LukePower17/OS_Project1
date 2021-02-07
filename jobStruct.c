#include "jobStruct.h"
#include <string.h>
#include "tokenlist.h"

jobStruct* copyJob(jobStruct* job)
{
    jobStruct* result = makejob(job->cmdNum, job->pid, job->tokens);
    return result;

}
jobStruct* newJob(void)
{
    jobStruct* job = (jobStruct *)malloc(sizeof(jobStruct));

    job->cmdNum = -1;
    job->pid = -1;
    job->command = NULL;
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

    job->command = new_tokenlist();
    for (int i = 0; i < tokens->size; i++)
    {
        add_token(job->command, tokens->items[i]);
    }
    // copy_tokenlist(tokens);


    return job;
}

char* getCommandJob(tokenlist* tokens)
{
    int size = 0;

    for(int i = 0; i < tokens->size; i++)
    {
        size += (strlen(tokens->items[i]) + 1);
    }


    char* command = (char*) malloc(size);

    strcpy(command, "");

    for(int i = 0; i < tokens->size; i++)
    {
        
        strcat(command, tokens->items[i]);
        if(i != tokens->size - 1)
            strcat(command, " ");
    }

    return command;
}
void printDone(jobStruct* job)
{
    char* name = getCommandJob(job->command);
    printf("[%d]+ [%ld] [%s]\n", job->cmdNum, (long)job->pid,name );

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

        printf("[%d]+ [%ld]\n", job->cmdNum, (long)job->pid);
    }
}

void freeJob(jobStruct* job)
{

    if(job == NULL)
    {
        return;
    }
   else
   {
        free(job);
        job = NULL;
    }
}
