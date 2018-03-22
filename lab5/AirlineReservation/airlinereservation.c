/* This is the shell you must fill in or replace in order to complete
   this project.
*/
#include <time.h>
#include "./airlinereservation.h"


int rows = COACH_ROWS + FIRST_ROWS;
int across = COACH_ACROSS;
#define SH_MEM_KEY getuid()

int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("Invalid Command! Please enter two elements!\n");
  }

  int customer;
  customer = atoi(argv[1]);
  char* output = argv[2];
  fclose(fopen(output, "w"));
  int ShmID = shmget(SH_MEM_KEY, sizeof(sharedMemory), IPC_CREAT| 0600);
  sharedMemory *SHDM = (sharedMemory *) shmat(ShmID, NULL, 0);
  sem_init(&(SHDM->firstClass), 1, 1);
  sem_init(&(SHDM->coach), 1, 1);
  sem_init(&(SHDM->mutex), 1, 1);

  createPlane(&(SHDM->currentP));
  printSeatsAvailable(&(SHDM->currentP));
  int i;
  for (i = 0; i < customer; i++) {
    if (fork() == 0) {
      executeChild(i, output, SH_MEM_KEY);
    }
  }


  int status;
  for (i = 0; i <customer; i++) {
    wait(&status);
  }

  shmdt((void *)SHDM);
  shmctl(ShmID, IPC_RMID, NULL);
  return 0;
}

void createPlane(plane* p) {
  int i, j;
  for (i = 0; i < MAX_ROWS; i++) {
    for (j = 0; j < MAX_ACROSS; j++) {
      p->seats[i][j] = 0;
    }
  }
}

void executeChild(int number, FILE* output, int key) {
  sharedMemory* SHDM;
  int sid = shmget(key, sizeof(sharedMemory), 0666);
  SHDM = (sharedMemory *) shmat(sid, NULL, 0);
  int chooseCoach = wantsCoachSeating(number);
  char* type;
  int seatNum = getNumberOfSeats(number, chooseCoach);
  int* map = (int*) malloc(seatNum * sizeof(int));
  int i;
  for (i = 0; i < seatNum && seatsRemaining(&(SHDM->currentP),
    chooseCoach) != 0; i++) {
    sem_wait(&(SHDM->mutex));
    if (chooseCoach) {
      type = "coach";
      printf("--------------------------------------------\n");
      sem_wait(&(SHDM->coach));
    } else {
      type = "first";
      printf("++++++++++++++++++++++++++++++++++++++++++++\n");
      sem_wait(&(SHDM->firstClass));
    }
    map[i] = reserveRandomSeat(&(SHDM->currentP), chooseCoach);
    printf("Customer %d reserved its %s seat No. %d (%d%c)\n",
      number, type, i, map[i]/COACH_ACROSS+1, 'A'+map[i]%COACH_ACROSS);
    printSeatsAvailable(&(SHDM->currentP));
    if (chooseCoach) {
      printf("--------------------------------------------\n");
      sem_post(&(SHDM->coach));
    } else {
      printf("++++++++++++++++++++++++++++++++++++++++++++\n");
      sem_post(&(SHDM->firstClass));
    }
    sem_post(&(SHDM->mutex));
  }
  printf("Customer #%d: %d %s seats reserved\n", number, i, type);
  writeToOutput(number, type, seatNum, map, output);
  free(map);
  map = NULL;
  exit(0);
}

void writeToOutput(int number, char* type, int seatNum,
                   int* map, char* output) {
  FILE* out = fopen(output, "a");
  fprintf(out, "Customer %d Purchase Receipt\n\n", number);
  fprintf(out, "%s Seats -- %d:\n\n", type, seatNum);

  int i;
  for (i = 0; i < seatNum; i ++) {
    int spot = map[i];
    fprintf(out, "\tSeat - %d%c\n", spot/COACH_ACROSS+1, 'A'+spot%COACH_ACROSS);
  }

  fprintf(out, "______________________________\n");
  fclose(out);
}
