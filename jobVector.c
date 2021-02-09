//Project 1
//COP4610
//Venkata Sai Pavan Kumar Vadrevu, Daniel Jamsheedy, Luke Power

#include "jobVector.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
// Returns a new jobVector
jobVector* new_jobVector(void)
{
    jobVector* result = (jobVector*) malloc(sizeof(jobVector));

    result->curSize = 0;
    result->size = 10;
    result->array = (jobStruct**) malloc(sizeof(jobStruct*) * result->size);

    result->array[0] = NULL;
    return result;

}

// Returns the index
int searchProcess(jobVector* V, pid_t pid)
{

    for(int i = 0; i < V->curSize; i++)
    {
        if((V->array[i])->pid == pid){
            printf("out of search Process\n");

            return i;
        }
    }

    return -1;
}

// returns the jobStruct
jobStruct* searchElement(jobVector* V, pid_t pid)
{
    int index = searchProcess(V, pid);
    jobStruct* result = NULL;
    if(index != -1)
    {
        result = V->array[index];
    }

    return result;
}

// returns 1 if remoced sucessfully
// 0 otherwise
int removeElement(jobVector* V, pid_t pid)
{

    int index = searchProcess(V, pid);

    if(index != -1 && V->curSize > 0)
    {
        jobStruct** tempArray = (jobStruct**) malloc(sizeof(jobStruct*) * V->size);

        for(int i = 0; i < V->size;i++)
        {
            if(i == index)
            {
                freeJob(V->array[i]);
                continue;
            }
            else
                tempArray[i] = copyJob(V->array[i]);

        }
        tempArray[V->size - 1] = newJob();

        // Free array in V
        for(int i = 0; i < V->size; i++)
        {
            freeJob(V->array[i]);
        }
        free(V->array);

        // Reallocate
        V->array = (jobStruct**) malloc(sizeof(jobStruct*) * V->size);

        // Copy Job fom tempArray
        V->array = tempArray;

        if(V->curSize > 0)
            V->curSize -= 1;

        return 1;
    }
    return 0;
}

// returns 1 if added sucessfully
// 0 otherwise
int appendElement(jobVector* V, jobStruct* job)
{

    V->array[V->curSize] = job;
    V->curSize++;

    return 1;

}



// free jobVector
void free_jobVector(jobVector* V)
{
    if(V != NULL)
    {
        for(int i = 0; i < V->size; i++)
        {
            freeJob(V->array[i]);
        }
        free(V->array);

        free(V);
    }
}

void printJobVector(jobVector* V)
{
    for(int i = 0; i < V->curSize; i++)
    {
        printf(">-----------------------------------------------\n");
              printf("cmd Num %d\n", V->array[i]->cmdNum);
              printf("pid %ld\n", (long)V->array[i]->pid);
              printf("completed %d\n", V->array[i]->completed);
              printf("time Taken %d\n", V->array[i]->timeTaken);
              printf("start Time %d\n", V->array[i]->startTime);
              printf("end Time%d\n", V->array[i]->endTime);
              printf("-----------------------------------------------\n");

    }
}

int runningCommandExists(jobVector* V)
{
    for(int i = 0; i < V->curSize; i++)
    {
        pid_t status = waitpid((V->array[i])->pid, NULL, WNOHANG);
        if(status == 0)
        {
            return 1;
        }

    }
    return 0;
}

void printCompletedJobs(jobVector* V, time_t current_time)
{
    int jobSize = 0;
    for(int i = 0; i < V->curSize; i++)
    {
        pid_t status = waitpid((V->array[i])->pid, NULL, WNOHANG);
        if(status != 0)
        {
            if(V->array[i]->completed == 0)
            {
                (V->array[i])->endTime = time(NULL);

                (V->array[i])->timeTaken = time(NULL) - (V->array[i])->startTime;
                if((V->array[i])->timeTaken > 0)
                {
                    (V->array[i])->timeTaken -= current_time;
                }

                (V->array[i])->completed = 1;
                printDone(V->array[i]);
                jobSize++;
            }
            else if((V->array[i])->completed == 1)
            {
                (V->array[i])->completed = 2;
            }
        }

    }
}


void printRunningJobs(jobVector* V)
{
    for(int i = 0; i < V->curSize; i++)
    {
        pid_t status = waitpid((V->array[i])->pid, NULL, WNOHANG);
        if(status == 0)
        {
            printDone(V->array[i]);
        }
    }
}
