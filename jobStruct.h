//Project 1
//COP4610
//Venkata Sai Pavan Kumar Vadrevu, Daniel Jamsheedy, Luke Power

#ifndef JOB_STRUCT_H
#define JOB_STRUCT_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>

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
jobStruct* copyJob(jobStruct* job);
char* getCommandJob(tokenlist* tokens);

void printJob(jobStruct* job);
void printDone(jobStruct* job);
void freeJob(jobStruct* job);


#endif
