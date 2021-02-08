//Project 1
//COP4610
//Venkata Sai Pavan Kumar Vadrevu, Daniel Jamsheedy, Luke Power

#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <pwd.h>
#include "EnvVariables.h"
#include "Tilde.h"
#include "tokenlist.h"


int hasTilde(tokenlist* tokens)
{
    for(int i = 0; i < tokens->size; i++)
    {
        if( (tokens->items[i])[0] == '~')
            return 1;
    }
    return 0;
}


char* expandTildeToken(char* token)
{
    char* tilde = (char*) malloc( strlen(getTilde()) + 1 + strlen(token));

    strcpy(tilde, "");
    if(strlen(token) >= 1){

        if(token[0] == '~')
        {
            strcat(tilde, getTilde());
        }
        strcat(tilde, token+1);
    }
    return tilde;
}

tokenlist* expandTilde(tokenlist* tokens)
{
    tokenlist* result = new_tokenlist();

    for(int i = 0; i < tokens->size; i++)
    {
        if(tokens->items[i][0] == '~')
        {
            char* tilde = expandTildeToken(tokens->items[i]);

            add_token(result, tilde);
            free(tilde);
        }
        else
        {
            add_token(result, tokens->items[i]);
        }
    }

    return result;
}

char *getTilde()
{
    char *result = NULL;
    result = getEnvironment("$HOME");
    return result;
}
