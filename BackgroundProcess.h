#ifndef BGPROCESS_H
#define BGPROCESS_H

#include "tokenlist.h"

// Checks if the group of tokens is a bakgorund process
int isBackgroundProcess(tokenlist* tokens);

tokenlist* getCommandFromBGProcess(tokenlist* tokens);


// Executes the process in backgorund and returns the time
// int backgroundProcess(tokenlist* tokens);

#endif