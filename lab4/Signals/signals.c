/* This is where you implement the core solution.
   by Zesun Yang and Yuchen Wang, <Date>
*/
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "./signals.h"

int alarm_fired = 0;
char* userName;
int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("not enough argument, enter an user name\n");
    exit(-1);
  }
  userName = argv[1];
  (void) signal(SIGINT, ouchQuit);
  (void) signal(SIGALRM, makeAlarm);
  (void) signal(SIGQUIT, list);
  (void) signal(SIGUSR1, killP);

  printf("the programming is waiting on something...\n");
  while (1) {
    alarm(5);
    sleep(5);
  }
  return 1;
}

void ouchQuit(int sig) {
    (void) signal(SIGINT, SIG_DFL);
    printf("\n");
    exit(0);
}
void makeAlarm(int sig) {
    if (sig == SIGALRM) {
        alarm_fired = 1;
    }
    printf("Ding!\007\n");
}

void list(int sig) {
    char buffer[512];
    snprintf(buffer, sizeof(buffer), "ps -u %s", userName);
    system(buffer);
}

void killP(int sig) {
    int pid;
    printf("enter PID to terminate process (kill -USR1 #)\n");
    scanf("%d", &pid);
    kill(pid, SIGUSR1);
}
