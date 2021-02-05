//Project 1
//COP4610
//Venkata Sai Pavan Kumar Vadrevu, Daniel Jamsheedy, Luke Power

// #include "BackgroundProcess.h"
#include "CD.h"
#include "CommandExe.h"
#include "Echo.h"
#include "EnvVariables.h"
#include "IO.h"
// #include "Jobs.h"
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
	


	
	while (1)
	{		

	time_t begin = time(NULL);
	char *input;
	time_t currentTime = 0;
	time_t mostTime = 0;

	do
	{

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


			//printf("Resolved path:\n");
			currentTime = commandExecution(tokens);

			// for (int i = 0; i < tokens->size; i++)
			// {
			// 	printf("token %d: (%s)\n", i, tokens->items[i]);
			// }

			if(currentTime > mostTime)
			{
				mostTime = currentTime;
			}

			if(strcmp(tokens->items[0],"cd") == 0)
			{
				changeDir(tokens);
			}

			// switch 1 ->
			// ...
			// ...   background process -> 
			commandExecution(command);

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

// int commandType(tokenlist* tokens)
// {

// 	// int function detects commandType 
// 	// -> background process  1
// 	// -> redirection         2
// 	// -> built in command    3
// 	// -> pipe                4
// 	// -> implemented         5
// 	// -> empty               0

// 	// 51234

// 	int result = 0;

// 	if(tokens->size > 0)
// 	{
// 		for(int i = 0; i < tokens->size; i++)
// 		{
// 			if((strcmp(tokens->items[i], ">") == 0) || (strcmp(tokens->items[i], "<") == 0))
// 			{
// 				if(result == 0)
// 				{
// 					result = REDIRECTION;
// 				}
// 				else
// 				{
// 					result *= 10;
// 					result += REDIRECTION;

// 				}
				
// 			}
// 			else if(strcmp(tokens->items[i], "|") == 0)
// 			{
// 				if(result == 0)
// 				{
// 					result = 1;
// 				}
// 				else
// 				{
// 					result *= 10;
// 				}
// 				result += PIPE;
// 			}
// 			else if(strcmp(tokens->items[i], "&") == 0)
// 			{
// 				if(result == 0)
// 				{
// 					result = ;
// 				}
// 				else
// 				{
// 					result *= 10;
// 				}
// 				result += BGPROCESS;
// 			}

// 			else if(strcmp(tokens->items[i], "$") == 0)
// 			{
// 				if(result == 0)
// 				{
// 					result = 1;
// 				}
// 				else
// 				{
// 					result *= 10;
// 				}
// 				result += VARIABLE;
// 			}
// 			else if( (strcmp(tokens->items[i], "echo") == 0) || ())
// 			{
// 				if(result == 0)
// 				{
// 					result = 1;
// 				}
// 				else
// 				{
// 					result *= 10;
// 				}
// 				result += VARIABLE;
// 			}
// 			else
// 			{
// 				if(result == 0)
// 				{
// 					result = 1;
// 				}
// 				else
// 				{
// 					result *= 10;
// 				}
// 				result += NORMALCOMMAND;
// 			}
// 		}
// 	}


// }
