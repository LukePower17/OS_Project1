#ifndef TILDE_H
#define TILDE_H

#include "tokenlist.h"

int hasTilde(tokenlist* tokens);
tokenlist* expandTilde(tokenlist* tokens);
char *getTilde();
char* expandTildeToken(char* token);

#endif