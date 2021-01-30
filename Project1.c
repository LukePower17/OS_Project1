//Project 1
//COP4610
//Venkata Sai Pavan Kumar Vadrevu, Daniel Jamsheedy, Luke Power

#include "BackgroundProcess.h"
#include "CD.h"
#include "CommandExe.h"
#include "Echo.h"
#include "EnvVariables.h"
#include "Exit.h"
#include "IO.h"
#include "Jobs.h"
#include "Path.h"
#include "Piping.h"
#include "Prompt.h"
#include "Tilde.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "tokenlist.h"
#include "Echo.h"


int main()
{
	while (1) {
		printPrompt();

		/* input contains the whole command
		 * tokens contains substrings from input split by spaces
		 */

		char *input = get_input();
		//printf("whole input: *%s*\n", input);

		if (input[0] != '\0'){
			/*
			Condition to check if input is empty
			Otherwise the properties of tokenlist will be null, resulting in crash
			*/

			tokenlist *tokens = get_tokens(input);

			for (int i = 0; i < tokens->size; i++)
	    {
				//printf("token %d: (%s)\n", i, tokens->items[i]);

	      //checks if the first character is a '$'
	      if(tokens->items[i][0] == '$')
	      {
						printEnvironment(tokens->items[i]);
	      }
			}

			//printf("Resolved path:\n");
			commandExecution(tokens);

			//echo(tokens);
			//printf("Back in main\n" );
			free_tokens(tokens);
		}
		free(input);
	}

	return 0;
}
