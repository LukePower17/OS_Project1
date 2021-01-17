//Project 1
//COP4610
//Venkata Sai Pavan Kumar Vadrevu, Daniel Jamsheedy, Luke Power

#include "EnvVariables.h"

void getEnvironment(char *name)
{
    printf("%s\n", getenv(name));   //Prints the enviroment variable to screen
}
