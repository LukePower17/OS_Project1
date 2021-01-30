//Project 1
//COP4610
//Venkata Sai Pavan Kumar Vadrevu, Daniel Jamsheedy, Luke Power

#include "Path.h"

char* pathSearch(char * command)
{
  char* path = getEnvironment("$PATH");
  char* token = strtok(path,":");

  char * a;
  int failure = 1;

   /* walk through other tokens */
   while( token != NULL && failure)
   {
      a = (char *)malloc( strlen(command) + strlen(token) + 2);
      strcat(a, token);
      strcat(a, "/");
      strcat(a, command);

      //printf("%s\n", a);
      failure = access(a, F_OK);

      if(failure)
      {
        free(a);
        token =  strtok(NULL,":");
      }
   }
   if (!failure){
     return a;
   }
   else
    return NULL;
}
