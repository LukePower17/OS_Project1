//Project 1
//COP4610
//Venkata Sai Pavan Kumar Vadrevu, Daniel Jamsheedy, Luke Power

#include "CD.h"
#include "CommandExe.h"
#include "Echo.h"
#include "EnvVariables.h"
#include "IO.h"
// #include "Jobs.h"
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


#define EMPTY 0
#define VARIABLE 1
#define NORMALCOMMAND 2
#define IMPLCOMMAND 3
#define REDIRECTION 4
#define PIPE 5
#define BGPROCESS 6


int commandType(tokenlist* tokens);

int main()
{


	// unordered map<cmdNum, num> Jobs

	// void Jobs(set* jobs)
		// vector<int> cmdNums
		//loop though
			// if jobs->isAlive
				// append the cmdNum

		// sort cmdNums

		// loop thorugh cmdNums
		//  Jobs[cmdNum].printJOb()




	char *input;

	time_t begin = time(NULL);
	time_t mostTime = 0;

	int BGProcessNum = 0;
	jobVector* jobsList = new_jobVector();

	do
	{
		time_t currentTime = 0;


		// Check if any job is complete
		for(int i = 0; i < jobList->curSize; i++)
		{
			jobStruct* job = jobList->array[i];
			pid_t pidJob = job->pid;

			pid_t status = waitpid(pidJob, NULL, WNOHANG);
			if(status != 0)
			{
				// process is finished
				printDone(jobList->array[i]);
				
			}
		}
		// from the map
		printPrompt();

		/* input contains the whole command
		 * tokens contains substrings from input split by spaces
		 */
		input = get_input();
		//printf("whole input: *%s*\n", input);


		if (input[0] != '\0')
		{
			/*
			Condition to check if input is empty
			Otherwise the properties of tokenlist will be null, resulting in crash
			*/

			tokenlist *tokens = get_tokens(input);

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
				printf("\nThis is a background process\n");
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
			else
			{
				currentTime = commandExecution(tokens);
			}

			if(currentTime > mostTime)
			{
				mostTime = currentTime;
			}

			if(strcmp(tokens->items[0],"cd") == 0)
			{
				changeDir(tokens);
			}

			//doPipe(tokens);

			// switch 1 ->
			// ...
			// ...   background process ->
			//commandExecution(command);

			// redirection(tokens);
			free_tokens(tokens);
		}
	}while(strcmp(input,"exit") != 0);

	free(input);

	time_t end = time(NULL);
	printf("Shell ran for %d seconds and took %d seconds to execute one command.\n", (int)(end - begin), (int)mostTime );

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