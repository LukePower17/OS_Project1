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
    pid_t pid;

} jobStruct;


jobStruct* newJob(void);
jobStruct* makejob(int cmdNum, pid_t pid ,tokenlist* command);
void printJob(jobStruct* job);
void freeJob(jobStruct* job);


#endif