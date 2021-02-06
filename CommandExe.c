//Project 1
//COP4610
//Venkata Sai Pavan Kumar Vadrevu, Daniel Jamsheedy, Luke Power

#include "CommandExe.h"


int commandExecution(tokenlist* tokens)
{
  time_t begin = time(NULL);

  char * resolvedPath = pathSearch(tokens->items[0]);

  if (resolvedPath == NULL)
  {
    printf("Error: Command not found.\n");
    return 0;
  }

  // using tokenlist as a c string container
  tokenlist *args = new_tokenlist();

  // store resolvedPath with remaining token list
  add_token(args, resolvedPath);
  for (int i = 1; i < tokens->size; i++)
  {
    add_token(args, tokens->items[i]);
  }

  int pid = fork();

  // child proccess executes command
  if (pid == 0)
  {
    execv(args->items[0], args->items);
    // child thread does not do anything after execution command
  }
  else
  {
    waitpid(pid, NULL, 0);
    // wait for child process to finish then continue
  }
  free_tokens(args);
  free(resolvedPath);

  time_t end = time(NULL);

  return (end - begin);
}
