/* Copyright 2016 Rose-Hulman

   But based on idea from http://cnds.eecs.jacobs-university.de/courses/caoslab-2007/
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>


int main(int argc, char *argv[]) {
  char command[82];
  /*infinite loop but ^C quits*/
  while (1) {
    printf("%% ");
    fgets(command, 82, stdin);
    if (command[0] == 'B' & command[1] == 'G') {
      int pid = fork();
      if (pid < 0) {
        printf("Fork failed.\n");
        return 1; /*nonzero means a failure result in unix*/
      } else if (pid == 0) {
        int forkID = fork();
        if (forkID < 0) {
          printf("Fork failed.\n");
          return 1; /*nonzero means a failure result in unix*/
        } else if (forkID == 0) {
          system(command+2);
          return 0;
        } else {
          wait(NULL);
          printf("Background command finished\n");
          return 0;
        }
      } else {}
    } else {
      waitpid(-1, NULL, WNOHANG);
      system(command);
    }
  }
  printf("exiting.\n");
  return 0;
}
