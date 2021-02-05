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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "tokenlist.h"
#include "Echo.h"

int main()
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
				//printf("token %d: (%s)\n", i, tokens->items[i]);

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

			//echo(tokens);
			//printf("Back in main\n" );
			free_tokens(tokens);
		}
	}while(strcmp(input,"exit") != 0);

		free(input);
		time_t end = time(NULL);
		printf("Shell ran for %d seconds and took %d seconds to execute one command.\n", (int)(end - begin), (int)mostTime );

	return 0;
}
