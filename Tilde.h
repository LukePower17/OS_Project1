//Project 1
//COP4610
//Venkata Sai Pavan Kumar Vadrevu, Daniel Jamsheedy, Luke Power

#ifndef TILDE_H
#define TILDE_H

#include "tokenlist.h"

int hasTilde(tokenlist* tokens);
tokenlist* expandTilde(tokenlist* tokens);
char *getTilde();
char* expandTildeToken(char* token);

#endif
