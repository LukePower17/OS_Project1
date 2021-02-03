//Project 1
//COP4610
//Venkata Sai Pavan Kumar Vadrevu, Daniel Jamsheedy, Luke Power

#include "CD.h"

void changeDir(tokenlist* tokens)
{
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
  setenv("PWD",cwd,1);
  free(cwd);
}
