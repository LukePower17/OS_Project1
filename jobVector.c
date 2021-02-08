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
    // printf("in new job Vector\n");

    jobVector* result = (jobVector*) malloc(sizeof(jobVector));

    result->curSize = 0;
    result->size = 0;
    result->array = (jobStruct**) malloc(sizeof(jobStruct*));

    result->array[0] = NULL;
    // printf("out of new job Vector\n");

    return result;

}

// DeepCopys a jobVector
jobVector* copy_jobVector(jobVector* V)
{
    // printf("in copy job Vector \n");

    jobVector* result = new_jobVector();

    result->size = V->size;
    result->curSize = V->curSize;

    free(result->array);

    result->array = (jobStruct**) malloc(sizeof(jobStruct*) * result->size);

    for(int i = 0; i < result->size; i++)
    {
        if(i < result->curSize)
        {
            result->array[i] = copyJob(V->array[i]);
        }
        else
        {
            result->array[i] = newJob();
        }
    }
    // printf("out of copy job Vector \n");

    return result;
}

// Resizes the vector
void resize(jobVector* V)
{
    // printf("in resize Element\n");

    if(V->size == V->curSize)
    {
        // Copyt the array
        jobStruct** tempArray = (jobStruct**) malloc(sizeof(jobStruct*) * V->size);
        
        for(int i = 0; i < V->size;i++)
        {
            if(i < V->curSize)
                tempArray[i] = copyJob(V->array[i]);
            else
                tempArray[i] = newJob();
        }

        // Free array in V
        for(int i = 0; i < V->size; i++)
        {
            freeJob(V->array[i]);
        }
        free(V->array);

        // Double the size
        V->size *= 2;

        // Reallocate
        V->array = (jobStruct**) malloc(sizeof(jobStruct*) * V->size);

        // Copy Job fom tempArray
        for(int i = 0; i < V->size; i++)
        {
            if(i < V->curSize)
                V->array[i] = copyJob(tempArray[i]);
            else
                V->array[i] = newJob();
        }

    }
    // printf("out of resize Element\n");

    return;
}

// Returns the index
int searchProcess(jobVector* V, pid_t pid)
{
    // printf("in search Process\n");

    for(int i = 0; i < V->curSize; i++)
    {
        if((V->array[i])->pid == pid){
            printf("out of search Process\n");

            return i;
        }
    }
    // printf("out of search Process\n");

    return -1;
}

// returns the jobStruct
jobStruct* searchElement(jobVector* V, pid_t pid)
{
    // printf("in search Element\n");

    int index = searchProcess(V, pid);
    jobStruct* result = NULL;
    if(index != -1)
    {
        result = V->array[index];
    }

    // printf("out of  search Element\n");
    // printf("index %d\n", index);
    return result;
}   

// returns 1 if remoced sucessfully
// 0 otherwise
int removeElement(jobVector* V, pid_t pid)
{

    // printf("in remove element\n");

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
        
        // printf("out of remove element\n");
        // printJobVector(V);
        return 1;
    }
    // printJobVector(V);

    // printf("out of remove element\n");

    return 0;
}

// returns 1 if added sucessfully
// 0 otherwise
int appendElement(jobVector* V, jobStruct* job)
{
    // printf("in append Element\n");
    if(V->curSize + 1 == V->size)
    {
        resize(V);
    }

    V->array[V->curSize] = job;
    V->curSize++;
    // printf("out of append Element\n");

    return 1;

}



// free jobVector
void free_jobVector(jobVector* V)
{
    // printf("in free job Vector Element\n");

    if(V != NULL)
    {
        for(int i = 0; i < V->size; i++)
        {
            freeJob(V->array[i]);
        }
        free(V->array);

        free(V);
    }

    // printf("out of free job Vector Element\n");

}

void printJobVector(jobVector* V)
{
    // printf("In print job vector\n");
    for(int i = 0; i < V->curSize; i++)
    {
        printf("%d ", i);
        if((V->array[i])->completed == 1)
            printJob(V->array[i]);
        else if((V->array[i])->completed == 0)
        {
            // printf("RUNNING\n");
            printJob(V->array[i]);

        }
        // printf("\n");
    }

    // printf("Out of print job vector\n");


}

int runningCommandExists(jobVector* V)
{
    for(int i = 0; i < V->curSize; i++)
    {
        pid_t status = waitpid((V->array[i])->pid, NULL, WNOHANG);
        if(status == 0)
        {
            // printf("RUNNING COMMAND EXISTS!\n");
            return 1;
        }

    }
    // printf("NO RUNNING COMMAND EXISTS!\n");

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

                (V->array[i])->timeTaken = (V->array[i])->endTime - (V->array[i])->startTime;
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
