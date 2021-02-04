//Project 1
//COP4610
//Venkata Sai Pavan Kumar Vadrevu, Daniel Jamsheedy, Luke Power

#include "Path.h"
#include <stdio.h>
char *pathSearch(char *command)
{
	// printf("In path Search\n");

	char *path = getEnvironment("$PATH");
	char *token = strtok(path, ":");

	// printf("path %s\n", path);
	// printf("token %s\n", token);

	char *a;
	int failure = 1;

	/* walk through other tokens */
	while (token != NULL && failure)
	{
		a = (char *)malloc(strlen(command) + strlen(token) + 2);
		strcat(a, token);
		strcat(a, "/");
		strcat(a, command);

		//printf("%s\n", a);
		failure = access(a, F_OK);

		if (failure)
		{
			free(a);
			token = strtok(NULL, ":");
		}
	}

	// printf("Out of path Seach\n");

	if (!failure)
	{
		return a;
	}
	else
		return NULL;
}
