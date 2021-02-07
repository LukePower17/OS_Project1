#include "jobVector.h"

// Returns a new jobVector
jobVector* new_jobVector(void)
{
    jobVector* result = (jobVector*) malloc(sizeof(jobVector));

    result->curSize = 0;
    result->size = 0;
    result->array = (jobStruct**) malloc(sizeof(jobStruct*));

    result->array[0] = NULL;

    return result;

}

// DeepCopys a jobVector
jobVector* copy_jobVector(jobVector* V)
{
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

    return result;
}

// Resizes the vector
void resize(jobVector* V)
{
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
    return;
}

// Returns the index
int searchProcess(jobVector* V, pid_t pid)
{
    for(int i = 0; i < V->curSize; i++)
    {
        if((V->array[i])->pid == pid)
            return i;
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
        result = V->array[i];
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

        // Reallocate
        V->array = (jobStruct**) malloc(sizeof(jobStruct*) * V->size);

        // Copy Job fom tempArray
        for(int i = 0; i < V->size; i++)
        {
            if(i == index)
                freeJob(V->array[i]);
            else if (i >= index)
                V->array[i] = V->array[i+1];
        }
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
    if(V->curSize + 1 == V->size)
    {
        resize(V);
    }

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