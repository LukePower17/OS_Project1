//Project 1
//COP4610
//Venkata Sai Pavan Kumar Vadrevu, Daniel Jamsheedy, Luke Power

#include "Path.h"

void pathSearch(char * command)
{
  char* path = getEnvironment("$PATH");

  /* get the first token */
   char* token = strtok(path,":");

   const char *a[100];
   int i = 0;

   FILE *fp;

   /* walk through other tokens */
   while( token != NULL ) {

      token =  strtok(NULL,":");
      a[i] = strtok(NULL,":");
      // strcat(a[i], "/");
      // strcat(a[i], command);
      
      printf("\n%s", a[i]);
      i++;
   }

}
