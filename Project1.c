//Project 1
//COP4610
//Venkata Sai Pavan Kumar Vadrevu, Daniel Jamsheedy, Luke Power

#include "CD.h"
#include "CommandExe.h"
#include "Echo.h"
#include "EnvVariables.h"
#include "IO.h"
#include "jobVector.h"
#include "BackgroundProcess.h"
#include "Path.h"
#include "Piping.h"
#include "Prompt.h"
#include "Tilde.h"
#include "jobStruct.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "tokenlist.h"
#include "Echo.h"



// int commandType(tokenlist* tokens);

int main()
{

	char *input;

	time_t begin = time(NULL);
	time_t mostTime = 0;
	time_t currentTime = 0;

	int BGProcessNum = 0;
	jobVector* jobList = new_jobVector();
	int exits = 0;

	do
	{	
		// printf("mostTIme %d\n", mostTime);
		// printJobVector(jobList);
		// from the map

 		printCompletedJobs(jobList, currentTime);
		// Update most time
		for(int i = 0; i < jobList->curSize; i++)
		{
			if( (mostTime) < (jobList->array[i]->timeTaken))
			{
				(mostTime) = (jobList->array[i]->timeTaken);
			}
		}

		currentTime = 0;

		printPrompt();



		/* input contains the whole command
		 * tokens contains substrings from input split by spaces
		 */
		input = get_input();
		//printf("whole input: *%s*\n", input);

		
		if (input[0] != '\0' && strcmp(input, "exit") != 0)
		{
			/*
			Condition to check if input is empty
			Otherwise the properties of tokenlist will be null, resulting in crash
			*/

			tokenlist *tokens = get_tokens(input);

			// tokenlist2d = Parse
			
			for (int i = 0; i < tokens->size; i++)
			{
				//checks if the first character is a '$'
				if (tokens->items[i][0] == '$')
				{
					printEnvironment(tokens->items[i]);
				}
			}

			int isBGProcess= isBackgroundProcess(tokens);

			if(isBGProcess == 1)
			{
				tokenlist* command = getCommandFromBGProcess(tokens);

				// add the pid to map

				pid_t pid = fork();
				jobStruct* job = makejob(BGProcessNum, pid, command);
				job->startTime = time(NULL);

				if(pid == 0)
				{
					commandExecution(command);
					exit(0);
				}

				printJob(job);
				appendElement(jobList, job);

				BGProcessNum++;
				free_tokens(command);
			}
			


			else if(strcmp(tokens->items[0],"cd") == 0)
			{
				changeDir(tokens);
			}

			else if(strcmp(tokens->items[0], "jobs") == 0)
			{
				printRunningJobs(jobList);
			}
			else
			{
				currentTime = commandExecution(tokens);
			}

			if(currentTime > (mostTime))
			{
				(mostTime) = currentTime;
			}


			free_tokens(tokens);
		}
		

		if(strcmp(input,"exit") == 0 && runningCommandExists(jobList) == 1)
		{
			printf("Waiting for background processes to finish ...\n");

		}

		exits = (strcmp(input, "exit") != 0 || runningCommandExists(jobList) == 1);

		// printf("exits: %d strcmp: %d  runningcmd: %d%\n", exits,(strcmp(input, "exit") != 0), (runningCommandExists(jobList) == 1));
	}while(exits != 0);

	if(jobList != NULL)
		free_jobVector(jobList);
	if(input != NULL)
		free(input);
	
	time_t end = time(NULL);
	printf("Shell ran for %d seconds and took %d seconds to execute one command.\n", (int)(end - begin), (int)(mostTime) );
	return 0;
}


// // A '|' C '|' E F
// 	// int function detects commandType
// 	// -> background process  1
// 	// -> redirection         2
// 	// -> built in command    3
// 	// -> pipe                4
// 	// -> implemented         5
// 	// -> empty               0


// #define EMPTY 0
// #define VARIABLE 1
// #define NORMALCOMMAND 2
// #define IMPLCOMMAND 3
// #define REDIRECTION 4
// #define PIPE 5
// #define BGPROCESS 6
