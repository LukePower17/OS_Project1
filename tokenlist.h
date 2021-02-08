//Project 1
//COP4610
//Venkata Sai Pavan Kumar Vadrevu, Daniel Jamsheedy, Luke Power

#ifndef TOKEN_LIST_H
#define TOKEN_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	int size;
	char **items;
} tokenlist;

char *get_input(void);
tokenlist *get_tokens(char *input);

tokenlist *new_tokenlist(void);
void add_token(tokenlist *tokens, char *item);
void free_tokens(tokenlist *tokens);

// ADDED FUNCTIONS

tokenlist *copy_tokenlist(tokenlist *tokens);
void print_tokens(tokenlist * tokens);

#endif
