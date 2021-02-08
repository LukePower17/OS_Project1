//Project 1
//COP4610
//Venkata Sai Pavan Kumar Vadrevu, Daniel Jamsheedy, Luke Power

#include "BackgroundProcess.h"
int isBackgroundProcess(tokenlist* tokens)
{
    for(int i = 0; i < tokens->size; i++)
    {
        if(strcmp(tokens->items[i], "&") == 0)
            return 1;
    }
    return 0;
}
tokenlist* getCommandFromBGProcess(tokenlist* tokens)
{
    tokenlist* result = new_tokenlist();

    for(int i = 0; i < tokens->size; i++)
    {
        if(strcmp(tokens->items[i], "&") == 0)
        {
            return result;
            break;
        }
        else{
            add_token(result, tokens->items[i]);
        }
    }

    return result;
}
