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

void doPipe(tokenlist* command);

tokenlist *some_tokens(tokenlist *tokens, int start, int end);

#endif
