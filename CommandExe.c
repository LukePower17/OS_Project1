//Project 1
//COP4610
//Venkata Sai Pavan Kumar Vadrevu, Daniel Jamsheedy, Luke Power

#include "CommandExe.h"

void commandExecution(tokenlist* tokens){
  char * resolvedPath = pathSearch(tokens->items[0]);

  if (resolvedPath == NULL){
    printf("Error: Command not found.\n");
    return;
  }

  // using tokenlist as a c string container
  tokenlist* args = new_tokenlist();

  // store resolvedPath with remaining token list
  add_token(args, resolvedPath);
  for(int i = 1; i < tokens->size; i++){
    add_token(args, tokens->items[i]);
  }

  int pid = fork();

  // child proccess executes command
  if (pid == 0){
    execv(args->items[0], args->items);
    free_tokens(args);
    free(resolvedPath);
  }
  else{
    waitpid(pid, NULL, 0);
  }
}
