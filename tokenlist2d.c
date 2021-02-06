#include "tokenlist2d.h"

tokenlist2d *new_tokenlist2d(void)
{
  tokenlist2d * result = (tokenlist2d *) malloc(sizeof(tokenlist2d));
  result->size = 0;
  result->lists = (tokenlist **) malloc(sizeof(tokenlist *));
  result->lists[0] = NULL;
  return result;
}

void add_list(tokenlist2d * list2d, tokenlist *list)
{
  int i = list2d->size;

  list2d->lists = (tokenlist **) realloc( list2d->lists, (i + 2) * sizeof(tokenlist *));
  list2d->lists[i] = copy_tokenlist(list);
  list2d->lists[i + 1] = NULL;

  list2d->size += 1;
}

void free_lists(tokenlist2d * list2d)
{
  for (int i = 0; i < list2d->size; i++)
    free_tokens(list2d->lists[i]);
  free(list2d->lists);
  free(list2d);
}

void print_list2d(tokenlist2d *list2d)
{
  for(int i = 0; i < list2d->size; i++)
  {
    print_tokens(list2d->lists[i]);
  }

}
