//Project 1
//COP4610
//Venkata Sai Pavan Kumar Vadrevu, Daniel Jamsheedy, Luke Power

#include "EnvVariables.h"

void printEnvironment(char *name)
{
    printf("%s", getEnvironment(name)); //Prints the enviroment variable to screen
}

char* getEnvironment(char * name){
  char * str = (char*)malloc(strlen(getenv(name + 1)) + 1);
  strcpy(str, getenv(name + 1));
  return str;
}
