//Project 1
//COP4610
//Venkata Sai Pavan Kumar Vadrevu, Daniel Jamsheedy, Luke Power

#include "Path.h"

char* pathSearch(char * command)
{
  char* path = getEnvironment("$PATH");
  char* token = strtok(path,":");
  char* errorMsg = "This command cannot be found\n";

  char *a[100];
  int i = 0;
  int success = 1;

   /* walk through other tokens */
   while( token != NULL )
   {
      a[i] = malloc( sizeof(*command) + (sizeof(*token)) + 2);
      strcat(a[i], token);
      strcat(a[i], "/");
      strcat(a[i], command);

      success = access(a[i], F_OK);
      if(success == 0)  //0 means success
      {
        return token;
      }
      i++;

      token =  strtok(NULL,":");
   }
   return errorMsg;
}
