//Project 1
//COP4610
//Venkata Sai Pavan Kumar Vadrevu, Daniel Jamsheedy, Luke Power

#include "Piping.h"
#include <time.h>


int doPipe(tokenlist *tokens){


	time_t begin = time(NULL);
	int numPipe = num_pipes(tokens);

	if (numPipe == 0)
		return (time(NULL) - begin);

	tokenlist2d * commands = parse_tokenlist(tokens, 0);

	if (commands == NULL)
		return (time(NULL) - begin);

	if (commands->size != numPipe + 1)
		return (time(NULL) - begin);

	// need to do commands == 3, which means 2 pipes
	if (commands->size == 2){
		int p1_to_p2[2];
	// slot 0 is output
	// slot 1 is input
		pipe(p1_to_p2);

	// 0 in
	// 1 stdout
	// 2 stderr
	// 3 p1_to_p2[0]
	// 4 p1_to_p2[1]

	int pid1 = fork();
	if (pid1 == 0)
	{
		close(1);  // close stdout
		dup(p1_to_p2[1]); // redirect output to slot 1

		// close extra spots
		close(3);
		close(4);

		commandExecution(commands->lists[0]);
		exit(1);
	}
	int pid2 = fork();
	if (pid2 == 0)
	{
		close(0); // close input
		dup(p1_to_p2[0]);
		close(3);
		close(4);

		commandExecution(commands->lists[1]);
		exit(1);
	}

	close(p1_to_p2[0]);
	close(p1_to_p2[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	}
	else if (commands->size == 3)
	{
	int p1_to_p2[2];
	int p2_to_p3[2];
	// slot 0 is output
	// slot 1 is input

	pipe(p1_to_p2);
	pipe(p2_to_p3);

	// 0 in
	// 1 stdout
	// 2 stderr
	// 3 p1_to_p2[0]
	// 4 p1_to_p2[1]

	// 5 p2_to_p3[0]
	// 6 p2_to_p3[1]

	int pid1 = fork();
	if (pid1 == 0)
	{
		// redirect output of current process

		// 1. close unused end of pipe
		close(p1_to_p2[0]); // not retriving output from previous process

		//2. channel process output(STDOUT == 1) to be input for next process
		dup2(p1_to_p2[1], 1); // close output, replace w current pfd
		close(p1_to_p2[1]); // close current pfd

		commandExecution(commands->lists[0]);
		exit(1);
	}
	int pid2 = fork();
	if (pid2 == 0)
	{
		// redirect input

		// 1. close the end we are not using
		close(p1_to_p2[1]); // close off pipe and esure input is read

		// 2. replace input (0) with pipe output from previous process and close
		dup2(p1_to_p2[0], 0); // close input, replace w current pfd
		close(p1_to_p2[0]);   // close extra copy

		// now to redirect command output

		// 1. close end of unused side of pipe
		close(p2_to_p3[0]); // close

		// 2. channel process output index 1 to be the input of pipe for next guy

		dup2(p2_to_p3[1], 1); // close output, replace with current pfd
		close(p2_to_p3[1]);   // close extra copy

		commandExecution(commands->lists[1]);
		exit(1);
	}
	int pid3 = fork();
	if (pid3 == 0)
	{
		// close unused pipe ends
		close(p1_to_p2[0]);
		close(p1_to_p2[1]);

		// close unused end of previous pipe
		close(p2_to_p3[1]);

		// redirect pipe input to be process input
		dup2(p2_to_p3[0], 0);
		close(p2_to_p3[0]);

		commandExecution(commands->lists[2]);
		exit(1);
	}

	// close all pipes of parent process
	close(p1_to_p2[0]);
	close(p1_to_p2[1]);
	close(p2_to_p3[0]);
	close(p2_to_p3[1]);

	// wait for child processes to finish before function return
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	waitpid(pid3, NULL, 0);
	}
	free_lists(commands);


	return time(NULL) - begin;
}

// Returns the number of pipes
int num_pipes(tokenlist * tokens)
{
	int count = 0;
	for(int i = 0; i < tokens->size; i++)
	{
	if(!strcmp(tokens->items[i], "|"))
		count++;
	}
	return count;
}

	// int ** p_fds = (int**)malloc(sizeof(int *) * pipes);
	// int * pids = (int*)malloc(sizeof(int) * commands->size);
	//
	// for(int i = 0; i < pipes; i++)
	//   p_fds[i] = (int*) malloc(sizeof(int) * 2);
	//
