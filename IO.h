//Project 1
//COP4610
//Venkata Sai Pavan Kumar Vadrevu, Daniel Jamsheedy, Luke Power

#ifndef IO_H
#define IO_H

#include "tokenlist.h"
#include <unistd.h>
#include <stdio.h>
#include <time.h>

int isValidRedirection(tokenlist *tokens);
char *isValidInputRedir(tokenlist *tokens);
char *isValidOutputRedir(tokenlist *tokens);
void getCommandIO(tokenlist* command, tokenlist *tokens);

int redirection(tokenlist *tokens);

void inputRedirection(tokenlist *command, char *inputFile);
void outputRedirection(tokenlist *command, char *outputFile);
void IORedirection(tokenlist *command, char *inputFile, char *outputFile);

#endif
