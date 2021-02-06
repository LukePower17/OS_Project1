#include "Piping.h"

void doPipe(tokenlist *tokens){

  printf("Do Pipe\n");
  int pipes = 0;
  int start = 0, end = 0;

  tokenlist2d * commands = new_tokenlist2d();

  while(end < tokens->size )
  {
    printf("%d, %d\n", start, end);
    if (strcmp(tokens->items[end], "|") == 0 || end + 1 == tokens->size)
    {
      if (end + 1 == tokens->size)
        end++;  // get substring from start up to tokens->size
      else
        pipes++;

      tokenlist *command = some_tokens(tokens, start, end);

      print_tokens(command);
      add_list(commands, command);
      free_tokens(command);

      end++;
      start = end;
    }
    else
      end++;
  }

  //print_list2d(commands);
  printf("Pipes: %d\nCommands: %d\n", pipes, commands->size);

  //int p_fds[2];
  // 0 is output of the pipe
  // 1 is input of the pipe
  //pipe(p_fds);


  free_lists(commands);
  //printf("Exit pipe\n");
}

tokenlist * some_tokens(tokenlist *tokens, int start, int end)
{
  tokenlist *result = new_tokenlist();
  for (int i = start; i < end; i++){
    add_token(result, tokens->items[i]);
  }
  return result;
}
