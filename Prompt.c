//Project 1
//COP4610
//Venkata Sai Pavan Kumar Vadrevu, Daniel Jamsheedy, Luke Power

#include "Prompt.h"
#include <stdio.h>

void printPrompt()
{

  char *user = getEnvironment("$USER");
  char *host = getEnvironment("$MACHINE");
  char *pwd = getEnvironment("$PWD");

  printf("%s@%s: %s>", user, host, pwd);

  free(user);
  free(host);
  free(pwd);

}
