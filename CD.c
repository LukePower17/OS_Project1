//Project 1
//COP4610
//Venkata Sai Pavan Kumar Vadrevu, Daniel Jamsheedy, Luke Power

#include "CD.h"

void changeDir(tokenlist* tokens)
{
  printf("inside chdir\n");
  if(tokens->size == 1)
  {
    //change to $HOME directory
    char* home = pathSearch("$HOME");
    chdir(home);
  }
  else
  {

  }
}
