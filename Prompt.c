//Project 1
//COP4610
//Venkata Sai Pavan Kumar Vadrevu, Daniel Jamsheedy, Luke Power

#include "Prompt.h"
#include <stdio.h>

void printPrompt()
{

  char *user = getEnvironment("$USER");
  char *host = getEnvironment("$HOST");
  char *pwd = getEnvironment("$PWD");

  printf("%s@%s: %s>", user, host, pwd);

  if (user != NULL)
    free(user);
  if (host != NULL)
    free(host);
  if (pwd != NULL)
    free(pwd);
}
