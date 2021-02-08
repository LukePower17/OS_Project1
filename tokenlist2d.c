#include "tokenlist2d.h"

tokenlist2d *new_tokenlist2d(void)
{
  tokenlist2d * result = (tokenlist2d *) malloc(sizeof(tokenlist2d));
  result->size = 0;
  result->lists = (tokenlist **) malloc(sizeof(tokenlist *));
  result->lists[0] = NULL;
  return result;
}

/*
parse_tokenlist expects a boolean value [0,1] for different ways of storing
example:
 A -u | B -o | C
 if (storeDelims == 1)
   result will be:
    A -u
    |
    B -o
    |
    C
  if storeDelims == 0
  result will be:
    A -u
    B -o
    C
*/

tokenlist2d *parse_tokenlist(tokenlist * tokens, int storeDelims)
{

  int start = 0, end = 0;
  tokenlist2d * result = new_tokenlist2d();

  tokenlist *command = NULL;
  while(end < tokens->size )
  {
    // | &
    if (!strcmp(tokens->items[end], "|"))
    {
      if (start == end || end + 1 == tokens->size)
      {
        printf("Invalid null command.\n");
        free_lists(result);
        return NULL;
      }

      command = some_tokens(tokens, start, end);
      add_list(result, command);
      free_tokens(command);
      command = NULL;

      start = end;
      if (storeDelims)
      {
        end++;
        command = some_tokens(tokens, start, end);
        add_list(result, command);
        free_tokens(command);
        command = NULL;
        start = end;
      }
      else
      {
        end++;
        start = end;
      }

    }
    else if (tokens->size == end + 1)
    {
      command = some_tokens(tokens, start, tokens->size);
      add_list(result, command);
      free_tokens(command);
      command = NULL;
      end++;
    }
    else
      end++;
  }
  return result;
}

tokenlist * some_tokens(tokenlist *tokens, int start, int end)
{
  tokenlist *result = new_tokenlist();
  for (int i = start; i < end; i++){
    add_token(result, tokens->items[i]);
  }
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
