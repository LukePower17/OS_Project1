#ifndef IO_H
#define IO_H

#include "tokenlist.h"
#include <unistd.h>
#include <stdio.h>

int isValid(tokenlist *tokens);

void redirection(tokenlist *tokens);

#endif
