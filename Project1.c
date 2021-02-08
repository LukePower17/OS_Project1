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
#include "tokenlist.h"
#include "tokenlist2d.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

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
			int numPipes = num_pipes(tokens);
			if(isBGProcess == 1)
			{
				// printf("\nThis is a background process\n");
				tokenlist* command = getCommandFromBGProcess(tokens);

				// add the pid to map

				pid_t pid = fork();
				jobStruct* job = makejob(BGProcessNum, pid, command);

				if(pid == 0)
				{
					currentTime = commandExecution(command);
					exit(0);
				}
				printJob(job);

				appendElement(jobList, job);

				// freeJob(job);
				BGProcessNum++;
				free_tokens(command);
			}
			else if(isValidRedirection(tokens) == 1)
			{
				currentTime = redirection(tokens);
			}
			else if(numPipes > 0)
			{

				currentTime = doPipe(tokens);
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


			

			// switch 1 ->
			// ...
			// ...   background process ->
			//commandExecution(command);
			printCompletedJobs(jobList, currentTime);

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


