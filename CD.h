//Project 1
//COP4610
//Venkata Sai Pavan Kumar Vadrevu, Daniel Jamsheedy, Luke Power
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "EnvVariables.h"
#include "tokenlist.h"

#ifndef CD_H
#define CD_H

void changeDir(tokenlist* tokens);
int setenv(const char *name, const char *value, int overwrite);
char *getcwd(char *buf, size_t size);

#endif
