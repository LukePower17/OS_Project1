#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <pwd.h>
#include "EnvVariables.h"

int hasTilde(tokenlist* tokens)
{
    for(int i = 0; i < tokens->size; i++)
    {
        if(strcmp(tokens->items[i], "~") == 0)
        {
            return 1;
        }
        if(strcmp(tokens->items[i], "~+") == 0)
        {
            return 2;
        }
        if(strcmp(tokens->items[i], "~-") == 0)
        {
            return 3;
        }
    }
    return 0;
}

void expandTilde(tokenlist* tokens)
{
    int val = hasTilde(tokens);

    if(val == 0)
    {
        // Do nothing
    }
    else if(val == 1)
    {


    }
    else if(val == 2)
    {

    }
    else if(val == 3)
    {

    }
}
char *getTilde(tokenlist* tokens)
{

    char *result = NULL;

    result = getenv("$HOME");

    if (result == NULL)
    {
        result = getpwuid(getuid())->pw_dir;
    }

    return result;
}

