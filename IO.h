#ifndef IO_H
#define IO_H

#include "tokenlist.h"
#include <unistd.h>
#include <stdio.h>

int isValid(tokenlist *tokens);
char *isValidInputRedir(tokenlist *tokens);
char *isValidOutputRedir(tokenlist *tokens);
void getCommand(tokenlist* command, tokenlist *tokens);

void redirection(tokenlist *tokens);

void inputRedirection(tokenlist *command, char *inputFile);
void outputRedirection(tokenlist *command, char *outputFile);
void IORedirection(tokenlist *command, char *inputFile, char *outputFile);

#endif
