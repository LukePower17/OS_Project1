#include "BackgroundProcess.h"
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

// Works for only one background process
int isBackgroundProcess(tokenlist* tokens)
{
    // If there is & in tokens then it is a backgorund process

    for(int i = 0; i < tokens->size; i++)
    {
        if(strcmp(tokens->items[i], "&") == 0)
            return 1;
    }

    return 0;
}


tokenlist* getCommandFromBGProcess(tokenlist* tokens)
{
    tokenlist* command =  new_tokenlist();

    int i = 0;

    while(i < tokens->size)
    {
        if(strcmp(tokens->items[i], "&") == 0)
        {
            break;
        }
        else
        {
            add_token(command, tokens->items[i]);
        }
        i++;
    }

    return command;
}


// int backgroundProcess(tokenlist* tokens)
// {

//     int timeTaken = 0;

//     int valid = isValid(tokens);

//     if(valid == 1)
//     {
//         // Need to add the job to unordered map
            
//             tokenlist* command = getCommand(tokens);

//             pid_t pid = fork();
//             // If the job is valid
            
//             if(pid == 0)
//             {
//                 timeTaken = commandExecution(command);
//             }
//             else
//             {
                
//                 while(waitpid(pid, NULL, WNOHANG) == 0)
//                 {
//                     //;
//                 }
//             }


//             // If the job is invalid we use exit command as the name


//     }
    
//     return timeTaken;
// }