#include "jobStruct.h"

jobStruct* newJob(void)
{
    jobStruct* job = (jobStruct *)malloc(sizeof(jobStruct));

    job->cmdNum = -1;
    job->name = "";
    job->isRunning = -1;
    job->pid = -1;
    job->timeTaken = -1;

    return job;
}

jobStruct* makejob(int cmdNum, char* name, int isRunning, pid_t pid)
{
    jobStruct* job = newJob();

    if(job == NULL)
    {
        job = newJob();
    }

    job->cmdNum = cmdNum;
    
    job->name = (char*)malloc(sizeof(strlen(name)+1));
    strcpy(job->name, name);

    job->timeTaken = 0;

    job->isRunning = isRunning;
    job->pid = pid;


    return job;
}

void printJob(jobStruct* job)
{

    if(job == NULL)
    {
        printf("NULL JOB\n");
    }
    else{
        printf("[%d]+ [%ld] [%s]\n", job->cmdNum, (long)job->pid, job->name);
    }
}

void freeJob(jobStruct* job)
{

    if(job == NULL)
    {
        return;
    }
    if(job != NULL){

        free(job->name);
        free(job);
        job = NULL;
    }
}