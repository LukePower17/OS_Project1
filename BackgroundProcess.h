#ifndef BGPROCESS_H
#define BGPROCESS_H
#include "tokenlist.h"

int isBackgroundProcess(tokenlist* tokens);
tokenlist* getCommandFromBGProcess(tokenlist* tokens);

#endif

