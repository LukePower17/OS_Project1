//Project 1
//COP4610
//Venkata Sai Pavan Kumar Vadrevu, Daniel Jamsheedy, Luke Power

#include <unistd.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "tokenlist.h"
#include "EnvVariables.h"
#include "Echo.h"
#include <stdio.h>

char *lowerCase(char *s)
{
    char *result = (char *)malloc(strlen(s) + 1);

    for (int i = 0; i < strlen(s) + 1; i++)
    {
        result[i] = tolower(result[i]);
    }

    return result;
}

int echo(tokenlist *tokens)
{
    time_t begin = time(NULL);
    // Check if the command is echo
    if (tokens->size > 0)
    {
        if (strcmp(tokens->items[0], "echo") == 0)
        {

            for (int i = 1; i < tokens->size; i++)
            {
                if ((tokens->items[i])[0] == '$')
                {
                    printEnvironment(tokens->items[i]);
                }
                else
                {
                    printf("%s", tokens->items[i]);
                }
            }
            printf("\n");
        }

    }

    return time(NULL) - begin;
}
