/* This is where you implement the core solution.
   by <Zesun Yang and Yuchen Wang>, <Date>
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "./processes.h"

int main(int argc, char *argv[]) {
    if (argc != 4) {
    printf("not enough arguement\n");
    exit(-1);
  }
  int n = atoi(argv[1]);  /* num of child */
  int x = atoi(argv[2]);  /*delay factor */
  /* FILE *inputF = fopen(argv[3], "r"); */
  struct timeval parentStartTime;
  gettimeofday(&parentStartTime, NULL);
  ProcessBox* processes = (ProcessBox*)malloc(n* sizeof(ProcessBox));
  int i;
  pid_t pid = getpid();
  for (i = 0; i < n; i++) {
    if (pid != 0) {
      pid = fork();
      processes[i].pid = pid;
      processes[i].index = i+1;
      struct timeval childStartTime;
      gettimeofday(&childStartTime, NULL);
      processes[i].startTime = childStartTime.tv_usec;
    } else if (pid == -1) {
      printf("fork failed\n");
      exit(-1);
    } else {
      break;
    }
  }

  char buffer[256];
  i--;
  if (pid == 0) { /*child process*/
    sleep((n-processes[i].index)*x/100000);
    FILE *inputF = fopen(argv[3], "r");
    int j;
    for (j =0; j < n; j++) {
      if (!fgets(buffer, 256, inputF)) {
        j--;
        rewind(inputF);
      }
      if (j == i) {
        /* fclose(inputF); */
        break;
      }
    }
    /* strcpy(buffer, "FileOne.txt"); */
    char childInputFile[256];
    char childOutputFile[256];
    fclose(inputF);
    strcpy(childInputFile, buffer);
    childInputFile[strlen(buffer)-1] = '\0';
    char temp[256];
    strcpy(temp, childInputFile);
    temp[strlen(childInputFile)-4] = '\0';
    sprintf(childOutputFile, "%s_%d_out.txt", temp, processes[i].index);
    execlp("./myCopy", "myCopy", childInputFile, childOutputFile, NULL);
  } else {
    struct timeval childEndTime;
    int k;
    pid_t finalPid = -1;
    for (k = 0; k < n; k++) {
      finalPid = wait(NULL);
      gettimeofday(&childEndTime, NULL);
      int m;
      for (m = 0; m < n; m++) {
        if (processes[m].pid == finalPid) {
          processes[m].endTime = childEndTime.tv_usec;
          int duration = 0;
          duration = processes[m].endTime-processes[m].startTime;
          printf("Time for process %d = %d microseconds\n",
            processes[m].index, duration);
	  /* fflush(stdout); */
        }
      }
    }
    struct timeval parentEndTime;
    gettimeofday(&parentEndTime, NULL);
    int parentDuartion = parentEndTime.tv_usec-parentStartTime.tv_usec;
    printf("All children are finished\n");
    printf("Parent time: %d microseconds\n", parentDuartion);
  }
  return 0;
}
