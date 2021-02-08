#include "jobStruct.h"

<<<<<<< Updated upstream
=======
jobStruct* copyJob(jobStruct* job)
{
    jobStruct* result = newJob();
    result->cmdNum = job->cmdNum;
    result->pid = job->pid;
    result->command = new_tokenlist();
    result->completed = job->completed;
    result->timeTaken = job->timeTaken;
    result->startTime = 0;
    result->endTime = 0;
    for (int i = 0; i < (job->command)->size; i++)
    {
        add_token(result->command, (job->command)->items[i]);
    }
    return result;
}

>>>>>>> Stashed changes
jobStruct* newJob(void)
{
    jobStruct* job = (jobStruct *)malloc(sizeof(jobStruct));

    job->cmdNum = -1;
    job->name = "";
    job->isRunning = -1;
    job->pid = -1;
<<<<<<< Updated upstream
    job->timeTaken = -1;

=======
    job->command = NULL;
    job->completed = 0;
    job->timeTaken = 0;
    job->startTime = 0;
    job->endTime = 0;
>>>>>>> Stashed changes
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
<<<<<<< Updated upstream
    
    job->name = (char*)malloc(sizeof(strlen(name)+1));
    strcpy(job->name, name);
=======
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
    // copy_tokenlist(tokens);


    return job;
}

char* getCommandJob(tokenlist* tokens)
{
    int size = 0;
>>>>>>> Stashed changes

    job->timeTaken = 0;

    job->isRunning = isRunning;
    job->pid = pid;


    return job;
}
<<<<<<< Updated upstream
=======
void printDone(jobStruct* job)
{
    char* name = getCommandJob(job->command);
    printf("[%d]+ [%ld] [%s]\n", job->cmdNum, (long)job->pid, name);
>>>>>>> Stashed changes

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