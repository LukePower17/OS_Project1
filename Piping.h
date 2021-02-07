//Project 1
//COP4610
//Venkata Sai Pavan Kumar Vadrevu, Daniel Jamsheedy, Luke Power

#ifndef PIPING_H
#define PIPING_H

#include <unistd.h>
#include <stdlib.h>

#include "tokenlist.h"
#include "tokenlist2d.h"
#include "string.h"
#include "CommandExe.h"

void doPipe(tokenlist* command);
int pipe_format(tokenlist *tokens);

tokenlist *some_tokens(tokenlist *tokens, int start, int end);
int num_pipes(tokenlist * tokens);

#endif
