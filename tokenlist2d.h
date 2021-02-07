#ifndef TOKENLIST2D
#define TOKENLIST2D

#include <stdlib.h>
#include "tokenlist.h"

typedef struct {
  int size;
  tokenlist **lists;
} tokenlist2d;


tokenlist2d *new_tokenlist2d(void);
void add_list(tokenlist2d * list2d, tokenlist *list);
void free_lists(tokenlist2d * list2d);

void print_list2d(tokenlist2d *list2d);

#endif