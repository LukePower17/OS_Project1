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

void echo(tokenlist *tokens)
{
    // printf("In Echo\n");
    // Check if the command is echo
    if (tokens->size > 0)
    {
        char *cmd = lowerCase(tokens->items[0]);

        if (strcmp(cmd, "echo") == 0)
        {
            // fork and then print the values
            int p_id = fork();

            if (p_id == 0)
            {
                for (int i = 1; i < tokens->size; i++)
                {
                    if ((tokens->items[i])[0] == '$')
                    {
                        // printenv(tokens->items[i]);
                    }
                    else
                    {
                        printf("%s", tokens->items[i]);
                    }
                }
                printf("\n");
            }
        }

        free(cmd);
    }
    // printf("Out of Echo\n");
}
