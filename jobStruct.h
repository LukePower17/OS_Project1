#ifndef JOB_STRUCT_H
#define JOB_STRUCT_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "tokenlist.h"

typedef struct{
    int cmdNum;
    int completed;
    int startTime;
    int endTime;
    int timeTaken;
    tokenlist* command;
} jobStruct;


jobStruct* newJob(void);
jobStruct* makejob(int cmdNum, char* name, int isRunning, pid_t pid);
void printJob(jobStruct* job);
void freeJob(jobStruct* job);


#endif