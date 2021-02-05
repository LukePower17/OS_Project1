#ifndef JOB_STRUCT_H
#define JOB_STRUCT_H

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
typedef struct{
    int cmdNum;
    char* name;
    int isRunning; // 0 is dead 1 if running
    int timeTaken;
    pid_t pid;

} jobStruct;


jobStruct* newJob(void);
jobStruct* makejob(int cmdNum, char* name, int isRunning, pid_t pid);
void printJob(jobStruct* job);
void freeJob(jobStruct* job);


#endif
