#include "Piping.h"

void doPipe(tokenlist *tokens){

  int numPipe = num_pipes(tokens);

  if (numPipe == 0)
    return;

  tokenlist2d * commands = parse_tokenlist(tokens, 0);

  if (commands == NULL)
    return;

  if (commands->size != numPipe + 1)
    return;

  print_list2d(commands);
  printf("numPipes: %d,\nCommands: %d\n", numPipe, commands->size);


  // need to do commands == 3, which means 2 pipes
  if (commands->size == 2){
    int p_fds[2];
    // slot 0 is output
    // slot 1 is input
    pipe(p_fds);

    // 0 in
    // 1 stdout
    // 2 stderr
    // pfds[0]
    // pfds[1]

    int pid1 = fork();
    if (pid1 == 0)
    {
      close(1);  // close stdout
      dup(p_fds[1]); // redirect output to slot 1

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
      dup(p_fds[0]);
      close(3);
      close(4);

      commandExecution(commands->lists[1]);
      exit(1);
    }
    close(p_fds[0]);
    close(p_fds[1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
  }
  free_lists(commands);
}

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
// for(int i = 0; i < commands->size; i++)
// {
//   if (i + 1 != commands->size)  // if there is a next command
//   {
//     pipe(p_fds[(i+1)/2]);
//   }
//   int pid = fork();
//   if (pid == 0)
//   {
//     if (i - 1 >= 0) // there is a previous command
//     {
//       dup2(p_fds[i/2][0], 0);
//       close(p_fds[i/2][0]);
//       close(p_fds[i/2][1]);
//     }
//     if (i + 1 != commands->size)  // there is a next command
//     {
//       close(p_fds[(i+1)/2][0]);
//       dup2(p_fds[(i+1)/2][1], 1);
//       close(p_fds[(i+1)/2][1]);
//     }
//     commandExecution(commands->lists[i]);
//     exit(1);
//   }
//   else
//   {
//     if (i - 1 >= 0)
//     {
//       close(p_fds[(i+1)/2][0]);
//       close(p_fds[(i+1)/2][1]);
//     }
//   }
// }

// for(int i = 0; i < pipes; i++)
// {
//   close(p_fds[i][0]);
//   close(p_fds[i][1]);
// }
