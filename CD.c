//Project 1
//COP4610
//Venkata Sai Pavan Kumar Vadrevu, Daniel Jamsheedy, Luke Power

#include "CD.h"
#include <time.h>

int changeDir(tokenlist* tokens)
{
  time_t begin = time(NULL);
  if(tokens->size == 1)
  {
    //change to $HOME directory
    char* home = getEnvironment("$HOME");
    chdir(home);
  }
  else
  {
    chdir(tokens->items[1]);
  }

  char *cwd = getcwd(NULL,0);
  if(cwd == NULL)
  {
    printf("DIRECTORY DOES NOT EXIST!!!!\n");
  }
  else{
    setenv("PWD",cwd,1);
    free(cwd);
  }

  return time(NULL) - begin;
}
