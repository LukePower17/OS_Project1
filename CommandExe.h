//Project 1
//COP4610
//Venkata Sai Pavan Kumar Vadrevu, Daniel Jamsheedy, Luke Power

#ifndef COMMANDEXE_H
#define COMMANDEXE_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

#include "Path.h"
#include "tokenlist.h"
#include <time.h>

int commandExecution(tokenlist* tokens);

#endif
