#ifndef __AIRPLANE_H__
#define __AIRPLANE_H__

/* This file is used to track the seats in an airplane */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "./input.h"


/* Used in shared memory to track seat reservations */
typedef struct {
    char seats[MAX_ROWS][MAX_ACROSS];
} plane;


/* Returns the number of seats still available on the plane */
int seatsRemaining(plane* p, int coachSeating);

/*
 * Attempts to reserve a seat at a given position 
 * Returns -1 if seat is already reserved and the seat number if 
 * the seat is reserved.
 */                                               
int reserveSeat(plane* p, int rowNum, int acrossNum);

/*
 * Reserves a random seat
 * Returns -1 if a seat cannot be reserved or the seat
 * number if a seat is reserved.
 */
int reserveRandomSeat(plane* p, int coachSeating);

/* Randomly determines if the customer wants coach or first class */
int wantsCoachSeating(int i);

/* Randomly determines the number of seats a customer wants to purchase */
int getNumberOfSeats(int i, int coachSeating);

/* Prints the plane and the seats still available */
void printSeatsAvailable(plane* p);

#endif /* __AIRPLANE_H__ */
