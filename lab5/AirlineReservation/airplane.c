/* This file is used to track the seats in an airplane */
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "./airplane.h"

extern int rows;
extern int across;

/* Returns the seats still available on the plane */
int seatsRemaining(plane* p, int coachSeating) {
  int start = 0, end = rows;
  int i, j, count = 0;

  if (coachSeating) {
    start+=FIRST_ROWS;
  } else {
    end = FIRST_ROWS;
  }

  for (i = start; i < end; i++) {
    for (j = 0; j < across; j++) {
      if (!(p->seats[i][j])) {
        count++;
      }
    }
  }
  return count;
}

/* Attempts to reserve a seat at a given position
   Returns -1 if seat is already reserved and the seat number 
   if it is available */
int reserveSeat(plane* p, int rowNum, int acrossNum) {
  int seatNumber = -1;
  if (p->seats[rowNum][acrossNum] > 0) {
    printf("Why Am I Here? This seat is already reserved. \n");
    fflush(stdout);
    return seatNumber;
  } else {
    p->seats[rowNum][acrossNum] = 1;
  }
  if (rowNum > FIRST_ROWS) {
    seatNumber = FIRST_ROWS*FIRST_ACROSS;
    seatNumber += ((rowNum-FIRST_ROWS)*COACH_ACROSS+acrossNum);
  } else {
    seatNumber =  rowNum*FIRST_ACROSS+acrossNum;
  }
  return seatNumber;
}

/* Reserves a random seat
   Returns -1 if a seat cannot be reserved and the 
   seat number if one is reserved.*/
int reserveRandomSeat(plane* p, int coachSeating) {
  int start = 0, end = rows, seatsLeft = 0;
  int rand, i, j, count;
  if (coachSeating) {
    start+=FIRST_ROWS;
  } else {
    end = FIRST_ROWS;
  }
  seatsLeft = seatsRemaining(p, coachSeating);
  if (seatsLeft == 0) {
    return -1;
  }

  rand = random()%seatsLeft;
  count = 0;
  for (i = start; i < end; i++) {
    for (j = 0; j < across; j++) {
      if (!(p->seats[i][j])) {
        if (count == rand) {
          return reserveSeat(p, i, j);
        } else {
          count++;
        }
      }
    }
  }
  printf("Final Spot\n");
  fflush(stdout);
  return -1;
}

/* Randomly determines if the customer wants coach or first class */
int wantsCoachSeating(int i) {
  srand(time(NULL)*(i+1));
  return (rand()%5) != 0;
}

/* Randomly determines the number of seats a customer wants to purchase */
int getNumberOfSeats(int i, int coachSeating) {
  int div = RAND_MAX, r, c = 0;
  srand(time(NULL)*(i+1));
  r = rand();
  if (!coachSeating) {
    while (r < div) {
      div = div/4;
      c++;
    }
  } else {
    while (r < div) {
      div = div/2;
      c++;
    }
  }
  return c;
}

/* Prints the plane and the seats still available */
void printSeatsAvailable(plane* p) {
  int i, j, k, q;
  for (i=0; i <= across; i++) {
    for (k=0; k <= rows; k++) {
      printf(" ");
    }
    for (j=across; j > i; j--) {
      printf(" ");
    }
    printf("/");
    for (j=i*2; j > 0; j--) {
      printf(" ");
    }
    printf("\\ \n");
  }
  for (i=0; i <= rows; i++) {
    for (k=0; k < rows; k++) {
      if (k == (rows-2*(i-rows*3/10))) {
        if (k == 0)
          printf(" ");
        printf("/");
      } else if (k == (rows-1-2*(i-rows*3/10))) {
        if (k == 0)
          printf(" ");
        printf("_");
      } else if (k == (rows-4*(i-2*rows*3/10))) {
        if (k == 0)
          printf("|");
        printf("/");
      } else if (k == (rows-1-4*(i-2*rows*3/10))) {
        if (k == 0)
          printf("|");
        printf("_");
      } else if (k == (rows-2-4*(i-2*rows*3/10))) {
        if (k == 0)
          printf("|");
        printf("_");
      } else if (k == (rows-3-4*(i-2*rows*3/10))) {
        if (k == 0)
          printf("|");
        printf("_");
      } else {
        if (k == 0)
          printf(" ");
        printf(" ");
      }
    }
    printf("|");
    if (i == FIRST_ROWS) {
      for (j = 0; j < across*2; j++)
        printf("_");
    } else {
      for (j = 0; j < across; j++) {
        if (j == isle) {
          printf(" ");
        }
        q = ((i > FIRST_ROWS)?i-1:i);
        if (p->seats[q][j]) {
          printf(" ");
        } else {
          printf("%c", (j+65));
        }
        if (j < (across - 1)) {
          printf(" ");
        }
      }
    }
    printf("|");
    for (k = 0; k < rows; k++) {
      if (k == 2*(i-rows*3/10)) {
        printf("_");
      } else if (k == 2*(i-rows*3/10)-1) {
        printf("\\");
      } else if (k == 4*(i-2*rows*3/10)) {
        printf("_");
        if (k == rows-1) {
          printf("|");
        }
      } else if (k == 4*(i-2*rows*3/10)-1) {
        printf("\\");
        if (k == rows-1) {
          printf("|");
        }
      } else if (k == 4*(i-2*rows*3/10)+2) {
        printf("_");
        if (k == rows-1) {
          printf("|");
        }
      } else if (k == 4*(i-2*rows*3/10)+1) {
        printf("_");
        if (k == rows-1) {
          printf("|");
        }
      } else {
        printf(" ");
      }
    }
    printf("\n");
  }
  for (k=0; k <= rows; k++) {
    printf(" ");
  }
  printf("|");
  for (i = 0; i < across; i++) {
    printf("__");
  }
  printf("|\n");
}
