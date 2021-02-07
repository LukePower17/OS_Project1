#ifndef JOB_STRUCT_H
#define JOB_STRUCT_H

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>

#include "tokenlist.h"

typedef struct{
    pid_t pid;
    int cmdNum;
    tokenlist* command;
} jobStruct;

jobStruct* copyJob(jobStruct* job);
jobStruct* newJob(void);
char* getCommandJob(tokenlist* tokens);
void printDone(jobStruct* job);
jobStruct* makejob(int cmdNum, pid_t pid, tokenlist* command);
void printJob(jobStruct* job);
void freeJob(jobStruct* job);

int isJobDone(jobStruct* job);

#endif
