#ifndef JOB_VECTOR_H
#define JOB_VECTOR_H

#include "jobStruct.h"

typedef struct{
    jobStruct** array;
    int curSize;
    int size;
} jobVector;


void free_array(jobStruct** array);

// Returns a new jobVector
jobVector* new_jobVector(void);

// DeepCopys a jobVector
jobVector* copy_jobVector(jobVector* V);

// Resizes the vector
void resize(jobVector* V);

// Returns the index
int searchProcess(jobVector* V,pid_t pid);

// returns the jobStruct
jobStruct* searchElement(jobVector* V, pid_t pid);

// returns 1 if remoced sucessfully
// 0 otherwise
int removeElement(jobVector* V, pid_t pid);

// returns 1 if added sucessfully
// 0 otherwise
int appendElement(jobVector* V, jobStruct* job);


// free jobVector
void free_jobVector(jobVector* V);
#endif