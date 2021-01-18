//Project 1
//COP4610
//Venkata Sai Pavan Kumar Vadrevu, Daniel Jamsheedy, Luke Power

#include "EnvVariables.h"

void getEnvironment(char *name)
{
    char* substr = name + 1;  //removes '$' from token
    printf("%s\n", getenv(substr));   //Prints the enviroment variable to screen
}
